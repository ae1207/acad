// dashboard.js

document.addEventListener('DOMContentLoaded', function() {
    // Initialize dashboard
    initializeDashboard();
    
    // Profile data storage
    let profileData = {
        height: 170, // cm
        weight: 70,  // kg
        age: 25,
        gender: 'Male',
        activity: 'Moderately Active',
        name: 'User'
    };

    // Load saved data or use defaults
    loadProfileData();
    
    function initializeDashboard() {
        updateDateTime();
        updateWelcomeMessage();
        calculateBMI();
        setupEventListeners();
        
        // Update date/time every minute
        setInterval(updateDateTime, 60000);
    }

    function loadProfileData() {
        const savedData = localStorage.getItem('healthyLifeProfile');
        if (savedData) {
            profileData = { ...profileData, ...JSON.parse(savedData) };
        }
        
        // Check for logged in user
        const userData = localStorage.getItem('healthyLifeUser');
        if (userData) {
            const user = JSON.parse(userData);
            profileData.name = user.email.split('@')[0]; // Use email prefix as name
        }
        
        updateProfileDisplay();
    }

    function saveProfileData() {
        localStorage.setItem('healthyLifeProfile', JSON.stringify(profileData));
    }

    function updateDateTime() {
        const now = new Date();
        const options = { 
            weekday: 'long', 
            year: 'numeric', 
            month: 'long', 
            day: 'numeric',
            hour: '2-digit',
            minute: '2-digit'
        };
        document.getElementById('currentDateTime').textContent = now.toLocaleDateString('en-US', options);
    }

    function updateWelcomeMessage() {
        const now = new Date();
        const hour = now.getHours();
        let greeting;
        
        if (hour < 12) {
            greeting = 'Good Morning';
        } else if (hour < 17) {
            greeting = 'Good Afternoon';
        } else {
            greeting = 'Good Evening';
        }
        
        document.getElementById('welcomeMessage').textContent = `${greeting}, ${profileData.name}!`;
    }

    function updateProfileDisplay() {
        document.getElementById('heightValue').textContent = `${profileData.height} cm`;
        document.getElementById('weightValue').textContent = `${profileData.weight} kg`;
        document.getElementById('ageValue').textContent = `${profileData.age} years`;
        document.getElementById('genderValue').textContent = profileData.gender;
        document.getElementById('activityValue').textContent = profileData.activity;
    }

    function calculateBMI() {
        const heightInM = profileData.height / 100;
        const bmi = profileData.weight / (heightInM * heightInM);
        const bmiRounded = Math.round(bmi * 10) / 10;
        
        document.getElementById('bmiValue').textContent = bmiRounded;
        
        // Update BMI category
        const categoryElement = document.getElementById('bmiCategory');
        const categoryBadge = categoryElement.querySelector('.category-badge');
        
        // Remove existing category classes
        categoryBadge.className = 'category-badge';
        
        // Update scale items
        const scaleItems = document.querySelectorAll('.scale-item');
        scaleItems.forEach(item => item.classList.remove('active'));
        
        if (bmi < 18.5) {
            categoryBadge.classList.add('underweight');
            categoryBadge.textContent = 'Underweight';
            scaleItems[0].classList.add('active');
        } else if (bmi < 25) {
            categoryBadge.classList.add('healthy');
            categoryBadge.textContent = 'Healthy Weight';
            scaleItems[1].classList.add('active');
        } else if (bmi < 30) {
            categoryBadge.classList.add('overweight');
            categoryBadge.textContent = 'Overweight';
            scaleItems[2].classList.add('active');
        } else {
            categoryBadge.classList.add('obese');
            categoryBadge.textContent = 'Obese';
            scaleItems[3].classList.add('active');
        }
    }

    function setupEventListeners() {
        // Logout button
        document.getElementById('logoutBtn').addEventListener('click', function() {
                window.location.href = 'TWTproject_main.html';
            }
        });

        // Goal calculator
        document.getElementById('calculateGoal').addEventListener('click', calculateGoal);

        // Modal controls
        setupModalControls();
    }

    function calculateGoal() {
        const goalType = document.getElementById('goalType').value;
        const targetWeight = parseFloat(document.getElementById('targetWeight').value);
        const timeframe = parseInt(document.getElementById('timeframe').value);
        
        if (!targetWeight || !timeframe) {
            alert('Please enter both target weight and timeframe');
            return;
        }

        const currentWeight = profileData.weight;
        const weightChange = targetWeight - currentWeight;
        const weeklyTarget = weightChange / timeframe;
        
        // Calculate BMR (Basal Metabolic Rate) using Mifflin-St Jeor Equation
        let bmr;
        if (profileData.gender === 'Male') {
            bmr = 10 * profileData.weight + 6.25 * profileData.height - 5 * profileData.age + 5;
        } else {
            bmr = 10 * profileData.weight + 6.25 * profileData.height - 5 * profileData.age - 161;
        }
        
        // Activity multiplier
        const activityMultipliers = {
            'Sedentary': 1.2,
            'Lightly Active': 1.375,
            'Moderately Active': 1.55,
            'Very Active': 1.725,
            'Extra Active': 1.9
        };
        
        const tdee = bmr * (activityMultipliers[profileData.activity] || 1.55);
        
        // Calorie adjustment (1 kg = ~7700 calories)
        const weeklyCalorieChange = weeklyTarget * 7700;
        const dailyCalorieChange = weeklyCalorieChange / 7;
        const dailyCalories = Math.round(tdee - dailyCalorieChange);
        
        // Update display
        document.getElementById('targetWeightDisplay').textContent = `${targetWeight} kg`;
        document.getElementById('weightChangeDisplay').textContent = `${weightChange > 0 ? '+' : ''}${weightChange} kg`;
        document.getElementById('weeklyTargetDisplay').textContent = `${weeklyTarget > 0 ? '+' : ''}${Math.round(weeklyTarget * 100) / 100} kg/week`;
        document.getElementById('dailyCaloriesDisplay').textContent = `${dailyCalories} kcal`;
        
        // Show results
        document.getElementById('goalResults').style.display = 'block';
        
        // Simulate progress (for demo)
        updateProgress();
    }

    function updateProgress() {
        // Simulate 2 weeks progress out of 8 weeks
        const progressPercent = 25; // 2/8 * 100
        document.getElementById('progressFill').style.width = progressPercent + '%';
        
        const progressStats = document.querySelector('.progress-stats');
        progressStats.innerHTML = `
            <span>Week 2 of 8</span>
            <span>${progressPercent}% Complete</span>
        `;
    }

    // Modal functionality
    let currentEditField = '';
    const modal = document.getElementById('editModal');
    const modalTitle = document.getElementById('modalTitle');
    const editLabel = document.getElementById('editLabel');
    const editInput = document.getElementById('editInput');
    const editForm = document.getElementById('editForm');

    function setupModalControls() {
        // Close modal
        document.getElementById('closeModal').addEventListener('click', closeModal);
        document.getElementById('cancelEdit').addEventListener('click', closeModal);
        
        // Submit form
        editForm.addEventListener('submit', function(e) {
            e.preventDefault();
            saveEdit();
        });
        
        // Click outside to close
        modal.addEventListener('click', function(e) {
            if (e.target === modal) {
                closeModal();
            }
        });
    }

    window.editProfile = function(field) {
        currentEditField = field;
        const fieldLabels = {
            'height': 'Height (cm)',
            'weight': 'Weight (kg)',
            'age': 'Age (years)',
            'gender': 'Gender',
            'activity': 'Activity Level'
        };
        
        modalTitle.textContent = `Edit ${fieldLabels[field]}`;
        editLabel.textContent = fieldLabels[field] + ':';
        
        if (field === 'gender') {
            editInput.type = 'text';
            editInput.value = profileData[field];
            editInput.placeholder = 'Male or Female';
        } else if (field === 'activity') {
            editInput.type = 'text';
            editInput.value = profileData[field];
            editInput.placeholder = 'e.g., Sedentary, Lightly Active, Moderately Active';
        } else {
            editInput.type = 'number';
            editInput.value = profileData[field];
            editInput.placeholder = `Enter ${fieldLabels[field].toLowerCase()}`;
        }
        
        modal.style.display = 'block';
        editInput.focus();
    };

    function closeModal() {
        modal.style.display = 'none';
        editForm.reset();
        currentEditField = '';
    }

    function saveEdit() {
        const newValue = editInput.value.trim();
        
        if (!newValue) {
            alert('Please enter a valid value');
            return;
        }
        
        if (currentEditField === 'gender') {
            const validGenders = ['Male', 'Female', 'male', 'female'];
            if (!validGenders.some(g => g.toLowerCase() === newValue.toLowerCase())) {
                alert('Please enter "Male" or "Female"');
                return;
            }
            profileData[currentEditField] = newValue.charAt(0).toUpperCase() + newValue.slice(1).toLowerCase();
        } else if (currentEditField === 'activity') {
            profileData[currentEditField] = newValue;
        } else {
            const numValue = parseFloat(newValue);
            if (isNaN(numValue) || numValue <= 0) {
                alert('Please enter a valid positive number');
                return;
            }
            
            // Validation ranges
            if (currentEditField === 'height' && (numValue < 100 || numValue > 250)) {
                alert('Height must be between 100-250 cm');
                return;
            }
            if (currentEditField === 'weight' && (numValue < 30 || numValue > 300)) {
                alert('Weight must be between 30-300 kg');
                return;
            }
            if (currentEditField === 'age' && (numValue < 10 || numValue > 120)) {
                alert('Age must be between 10-120 years');
                return;
            }
            
            profileData[currentEditField] = numValue;
        }
        
        saveProfileData();
        updateProfileDisplay();
        calculateBMI();
        closeModal();
        
        // Show success message
        showNotification('Profile updated successfully!');
    }

    function showNotification(message) {
        const notification = document.createElement('div');
        notification.style.cssText = `
            position: fixed;
            top: 20px;
            right: 20px;
            background: #4CAF50;
            color: white;
            padding: 1rem 1.5rem;
            border-radius: 8px;
            box-shadow: 0 5px 15px rgba(0,0,0,0.2);
            z-index: 3000;
            animation: slideInRight 0.3s ease;
        `;
        notification.textContent = message;
        
        document.body.appendChild(notification);
        
        setTimeout(() => {
            notification.style.animation = 'slideOutRight 0.3s ease';
            setTimeout(() => {
                document.body.removeChild(notification);
            }, 300);
        }, 3000);
    }

    // Add CSS animations for notifications
    const style = document.createElement('style');
    style.textContent = `
        @keyframes slideInRight {
            from {
                transform: translateX(100%);
                opacity: 0;
            }
            to {
                transform: translateX(0);
                opacity: 1;
            }
        }
        
        @keyframes slideOutRight {
            from {
                transform: translateX(0);
                opacity: 1;
            }
            to {
                transform: translateX(100%);
                opacity: 0;
            }
        }
    `;
    document.head.appendChild(style);

    // Animate stats on load
    function animateStats() {
        const statCards = document.querySelectorAll('.stat-card');
        statCards.forEach((card, index) => {
            card.style.opacity = '0';
            card.style.transform = 'translateY(20px)';
            
            setTimeout(() => {
                card.style.transition = 'all 0.5s ease';
                card.style.opacity = '1';
                card.style.transform = 'translateY(0)';
            }, index * 100);
        });
    }

    // Simulate real-time updates for demo
    function simulateRealTimeUpdates() {
        // Update water intake randomly
        setInterval(() => {
            const waterElement = document.querySelector('.stat-card:nth-child(2) .stat-value');
            const current = parseInt(waterElement.textContent.split('/')[0]);
            if (current < 8 && Math.random() > 0.7) {
                waterElement.textContent = `${current + 1} / 8 glasses`;
                const progressElement = waterElement.parentElement.querySelector('.stat-progress');
                progressElement.textContent = `${Math.round((current + 1) / 8 * 100)}%`;
            }
        }, 30000); // Every 30 seconds

        // Update steps
        setInterval(() => {
            const stepsElement = document.querySelector('.stat-card:nth-child(3) .stat-value');
            const current = parseInt(stepsElement.textContent.split('/')[0].replace(',', ''));
            if (current < 10000 && Math.random() > 0.8) {
                const newSteps = current + Math.floor(Math.random() * 100) + 50;
                stepsElement.textContent = `${newSteps.toLocaleString()} / 10,000`;
                const progressElement = stepsElement.parentElement.querySelector('.stat-progress');
                progressElement.textContent = `${Math.round(newSteps / 10000 * 100)}%`;
            }
        }, 45000); // Every 45 seconds
    }

    // Mobile responsiveness - remove sidebar functionality
    function setupMobileMenu() {
        // No sidebar functionality needed anymore
        return;
    }

    // Check authentication
    function checkAuth() {
        const userData = localStorage.getItem('healthyLifeUser');
        if (!userData) {
            window.location.href = 'login.html';
            return false;
        }
        return true;
    }

    // Initialize everything
    if (checkAuth()) {
        animateStats();
        simulateRealTimeUpdates();
        setupMobileMenu();
        
        // Update mobile menu on resize
        window.addEventListener('resize', function() {
            // No mobile menu functionality needed
        });
    }

    // Keyboard shortcuts
    document.addEventListener('keydown', function(e) {
        // Escape to close modal
        if (e.key === 'Escape' && modal.style.display === 'block') {
            closeModal();
        }
        
        // Ctrl/Cmd + L to logout
        if ((e.ctrlKey || e.metaKey) && e.key === 'l') {
            e.preventDefault();
            document.getElementById('logoutBtn').click();
        }
    });

    // Add smooth scrolling for better UX
    document.documentElement.style.scrollBehavior = 'smooth';

    // Initialize tooltips for better UX
    function initializeTooltips() {
        const editButtons = document.querySelectorAll('.edit-btn');
        editButtons.forEach(btn => {
            btn.title = 'Click to edit this value';
        });
        
        const notificationBtn = document.querySelector('.notification-btn');
        if (notificationBtn) {
            notificationBtn.title = 'View notifications';
        }
    }

    initializeTooltips();

    // Auto-save feature for forms
    const inputs = document.querySelectorAll('#goalType, #targetWeight, #timeframe');
    inputs.forEach(input => {
        input.addEventListener('change', function() {
            const goalData = {
                goalType: document.getElementById('goalType').value,
                targetWeight: document.getElementById('targetWeight').value,
                timeframe: document.getElementById('timeframe').value
            };
            localStorage.setItem('healthyLifeGoalData', JSON.stringify(goalData));
        });
    });

    // Load saved goal data
    function loadGoalData() {
        const savedGoalData = localStorage.getItem('healthyLifeGoalData');
        if (savedGoalData) {
            const goalData = JSON.parse(savedGoalData);
            if (goalData.goalType) document.getElementById('goalType').value = goalData.goalType;
            if (goalData.targetWeight) document.getElementById('targetWeight').value = goalData.targetWeight;
            if (goalData.timeframe) document.getElementById('timeframe').value = goalData.timeframe;
        }
    }

    loadGoalData();

    // Performance optimization - lazy load animations
    const observerOptions = {
        threshold: 0.1,
        rootMargin: '0px 0px -50px 0px'
    };

    const cardObserver = new IntersectionObserver(function(entries) {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                entry.target.style.animation = 'slideInUp 0.6s ease forwards';
                cardObserver.unobserve(entry.target);
            }
        });
    }, observerOptions);

    // Observe all cards for animation
    document.querySelectorAll('.card').forEach(card => {
        card.style.opacity = '0';
        card.style.transform = 'translateY(30px)';
        cardObserver.observe(card);
    });

    // Add slideInUp animation
    const animationStyle = document.createElement('style');
    animationStyle.textContent += `
        @keyframes slideInUp {
            from {
                opacity: 0;
                transform: translateY(30px);
            }
            to {
                opacity: 1;
                transform: translateY(0);
            }
        }
    `;
    document.head.appendChild(animationStyle);

    // Error handling for localStorage
    function safeLocalStorage() {
        try {
            return localStorage;
        } catch (e) {
            console.warn('localStorage not available:', e);
            return {
                getItem: () => null,
                setItem: () => {},
                removeItem: () => {}
            };
        }
    }

    // Replace localStorage calls with safe version
    window.safeLocalStorage = safeLocalStorage();

    console.log('HealthyLife Dashboard initialized successfully!');
});

