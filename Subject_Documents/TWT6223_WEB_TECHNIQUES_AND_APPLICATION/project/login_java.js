document.addEventListener('DOMContentLoaded', function() {
    // Get form elements
    const loginForm = document.getElementById('loginForm');
    const emailInput = document.getElementById('email');
    const passwordInput = document.getElementById('password');
    const togglePassword = document.getElementById('togglePassword');
    const emailError = document.getElementById('emailError');
    const passwordError = document.getElementById('passwordError');
    const successModal = document.getElementById('successModal');
    const signupLink = document.getElementById('signupLink');

    // Password toggle functionality
    togglePassword.addEventListener('click', function() {
        const type = passwordInput.getAttribute('type') === 'password' ? 'text' : 'password';
        passwordInput.setAttribute('type', type);
        this.textContent = type === 'password' ? '👁️' : '🙈';
    });

    // Email validation
    function validateEmail(email) {
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        return emailRegex.test(email);
    }

    // Password validation
    function validatePassword(password) {
        return password.length >= 6;
    }

    // Show error message
    function showError(element, message) {
        element.textContent = message;
        element.style.color = '#e74c3c';
    }

    // Clear error message
    function clearError(element) {
        element.textContent = '';
    }

    // Real-time validation
    emailInput.addEventListener('blur', function() {
        const email = this.value.trim();
        if (email && !validateEmail(email)) {
            showError(emailError, 'Please enter a valid email address');
            this.style.borderColor = '#e74c3c';
        } else {
            clearError(emailError);
            this.style.borderColor = '#e1e5e9';
        }
    });

    emailInput.addEventListener('input', function() {
        if (this.style.borderColor === 'rgb(231, 76, 60)') {
            this.style.borderColor = '#e1e5e9';
            clearError(emailError);
        }
    });

    passwordInput.addEventListener('blur', function() {
        const password = this.value;
        if (password && !validatePassword(password)) {
            showError(passwordError, 'Password must be at least 6 characters long');
            this.style.borderColor = '#e74c3c';
        } else {
            clearError(passwordError);
            this.style.borderColor = '#e1e5e9';
        }
    });

    passwordInput.addEventListener('input', function() {
        if (this.style.borderColor === 'rgb(231, 76, 60)') {
            this.style.borderColor = '#e1e5e9';
            clearError(passwordError);
        }
    });

    // Form submission
    loginForm.addEventListener('submit', function(e) {
        e.preventDefault();
        
        const email = emailInput.value.trim();
        const password = passwordInput.value;
        const rememberMe = document.getElementById('rememberMe').checked;
        
        let isValid = true;

        // Validate email
        if (!email) {
            showError(emailError, 'Email is required');
            emailInput.style.borderColor = '#e74c3c';
            isValid = false;
        } else if (!validateEmail(email)) {
            showError(emailError, 'Please enter a valid email address');
            emailInput.style.borderColor = '#e74c3c';
            isValid = false;
        } else {
            clearError(emailError);
            emailInput.style.borderColor = '#4CAF50';
        }

        // Validate password
        if (!password) {
            showError(passwordError, 'Password is required');
            passwordInput.style.borderColor = '#e74c3c';
            isValid = false;
        } else if (!validatePassword(password)) {
            showError(passwordError, 'Password must be at least 6 characters long');
            passwordInput.style.borderColor = '#e74c3c';
            isValid = false;
        } else {
            clearError(passwordError);
            passwordInput.style.borderColor = '#4CAF50';
        }

        if (isValid) {
            // Show loading state
            const submitBtn = document.querySelector('.login-btn');
            const originalText = submitBtn.textContent;
            submitBtn.textContent = 'Signing In...';
            submitBtn.disabled = true;
            submitBtn.style.opacity = '0.7';

            // Simulate login process
            setTimeout(() => {
                // Store user data (in a real app, this would be handled by backend)
                const userData = {
                    email: email,
                    loginTime: new Date().toISOString(),
                    rememberMe: rememberMe
                };

                // Store in localStorage for demo purposes
                localStorage.setItem('healthyLifeUser', JSON.stringify(userData));

                // Show success modal
                successModal.style.display = 'block';

                // Redirect to dashboard after 2 seconds
                setTimeout(() => {
                    window.location.href = 'TWTproject_dashboard.html';
                }, 2000);

            }, 1500);
        }
    });

    // Signup link
    signupLink.addEventListener('click', function(e) {
        e.preventDefault();
        alert('Signup page would be implemented here');
    });

    // Forgot password link
    const forgotPasswordLink = document.querySelector('.forgot-password');
    forgotPasswordLink.addEventListener('click', function(e) {
        e.preventDefault();
        
        const email = emailInput.value.trim();
        if (email && validateEmail(email)) {
            alert(`Password reset link would be sent to: ${email}`);
        } else {
            alert('Please enter a valid email address first');
            emailInput.focus();
        }
    });

    // Close modal when clicking outside
    successModal.addEventListener('click', function(e) {
        if (e.target === this) {
            this.style.display = 'none';
        }
    });

    // Enter key submission
    document.addEventListener('keydown', function(e) {
        if (e.key === 'Enter' && !e.shiftKey) {
            const focusedElement = document.activeElement;
            if (focusedElement === emailInput || focusedElement === passwordInput) {
                loginForm.dispatchEvent(new Event('submit'));
            }
        }
    });

    // Auto-fill demo credentials button (for testing)
    const demoButton = document.createElement('button');
    demoButton.textContent = 'Fill Demo Credentials';
    demoButton.type = 'button';
    demoButton.style.cssText = `
        background: #f8f9fa;
        border: 1px solid #e1e5e9;
        color: #666;
        padding: 0.5rem 1rem;
        border-radius: 5px;
        font-size: 0.8rem;
        cursor: pointer;
        margin-top: 1rem;
        width: 100%;
    `;
    
    demoButton.addEventListener('click', function() {
        emailInput.value = 'demo@healthylife.com';
        passwordInput.value = 'demo123';
    });
    
    loginForm.appendChild(demoButton);

    // Add entrance animation
    document.body.style.opacity = '0';
    setTimeout(() => {
        document.body.style.transition = 'opacity 0.5s ease';
        document.body.style.opacity = '1';
    }, 100);

    // Add focus effects
    const inputs = document.querySelectorAll('input[type="email"], input[type="password"]');
    inputs.forEach(input => {
        input.addEventListener('focus', function() {
            this.parentElement.style.transform = 'translateY(-2px)';
            this.parentElement.style.transition = 'transform 0.3s ease';
        });
        
        input.addEventListener('blur', function() {
            this.parentElement.style.transform = 'translateY(0)';
        });
    });

    // Check if user is already logged in
    const storedUser = localStorage.getItem('healthyLifeUser');
    if (storedUser) {
        const userData = JSON.parse(storedUser);
        if (userData.rememberMe) {
            // Auto-redirect to dashboard if remember me was checked
            setTimeout(() => {
                window.location.href = 'TWTproject_dashboard.html';
            }, 1000);
        }
    }
});