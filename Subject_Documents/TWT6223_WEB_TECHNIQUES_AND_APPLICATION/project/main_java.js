document.addEventListener('DOMContentLoaded', function() {
    // Smooth scrolling for navigation links
    const navLinks = document.querySelectorAll('a[href^="#"]');
    
    navLinks.forEach(link => {
        link.addEventListener('click', function(e) {
            e.preventDefault();
            
            const targetId = this.getAttribute('href').substring(1);
            const targetElement = document.getElementById(targetId);
            
            if (targetElement) {
                targetElement.scrollIntoView({
                    behavior: 'smooth',
                    block: 'start'
                });
            }
        });
    });

    // Add scroll effect to navbar
    window.addEventListener('scroll', function() {
        const navbar = document.querySelector('.navbar');
        if (window.scrollY > 100) {
            navbar.style.background = 'rgba(255, 255, 255, 0.95)';
            navbar.style.backdropFilter = 'blur(10px)';
        } else {
            navbar.style.background = 'white';
            navbar.style.backdropFilter = 'none';
        }
    });

    // Animate feature cards on scroll
    const observerOptions = {
        threshold: 0.1,
        rootMargin: '0px 0px -50px 0px'
    };

    const observer = new IntersectionObserver(function(entries) {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                entry.target.style.opacity = '1';
                entry.target.style.transform = 'translateY(0)';
            }
        });
    }, observerOptions);

    // Observe feature cards
    const featureCards = document.querySelectorAll('.feature-card');
    featureCards.forEach((card, index) => {
        card.style.opacity = '0';
        card.style.transform = 'translateY(50px)';
        card.style.transition = `opacity 0.6s ease ${index * 0.1}s, transform 0.6s ease ${index * 0.1}s`;
        observer.observe(card);
    });

    // Animate stats counter
    function animateCounter(element, target) {
        let current = 0;
        const increment = target / 100;
        const timer = setInterval(() => {
            current += increment;
            if (current >= target) {
                current = target;
                clearInterval(timer);
            }
            
            if (target >= 1000) {
                element.textContent = Math.floor(current).toLocaleString() + '+';
            } else {
                element.textContent = Math.floor(current) + '%';
            }
        }, 20);
    }

    // Observe stats section
    const statsSection = document.querySelector('.stats');
    const statsObserver = new IntersectionObserver(function(entries) {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                const statNumbers = entry.target.querySelectorAll('.stat h3');
                statNumbers.forEach(stat => {
                    const text = stat.textContent;
                    const number = parseInt(text.replace(/[^\d]/g, ''));
                    animateCounter(stat, number);
                });
                statsObserver.unobserve(entry.target);
            }
        });
    });

    if (statsSection) {
        statsObserver.observe(statsSection);
    }

    // Add hover effect to CTA buttons
    const ctaButtons = document.querySelectorAll('.btn-primary, .btn-secondary');
    ctaButtons.forEach(button => {
        button.addEventListener('mouseenter', function() {
            this.style.transform = 'translateY(-3px) scale(1.05)';
        });
        
        button.addEventListener('mouseleave', function() {
            this.style.transform = 'translateY(0) scale(1)';
        });
    });

    // Mobile menu toggle (if needed for responsive design)
    const navbar = document.querySelector('.navbar');
    let isMenuOpen = false;

    // Add mobile menu button if screen is small
    function checkScreenSize() {
        if (window.innerWidth <= 768) {
            if (!document.querySelector('.mobile-menu-btn')) {
                const menuBtn = document.createElement('button');
                menuBtn.innerHTML = '☰';
                menuBtn.className = 'mobile-menu-btn';
                menuBtn.style.cssText = `
                    display: block;
                    background: none;
                    border: none;
                    font-size: 1.5rem;
                    color: #333;
                    cursor: pointer;
                `;
                
                menuBtn.addEventListener('click', toggleMobileMenu);
                navbar.appendChild(menuBtn);
            }
        } else {
            const menuBtn = document.querySelector('.mobile-menu-btn');
            if (menuBtn) {
                menuBtn.remove();
            }
        }
    }

    function toggleMobileMenu() {
        const navLinks = document.querySelector('.nav-links');
        isMenuOpen = !isMenuOpen;
        
        if (isMenuOpen) {
            navLinks.style.display = 'flex';
            navLinks.style.flexDirection = 'column';
            navLinks.style.position = 'absolute';
            navLinks.style.top = '100%';
            navLinks.style.left = '0';
            navLinks.style.right = '0';
            navLinks.style.background = 'white';
            navLinks.style.padding = '1rem';
            navLinks.style.boxShadow = '0 2px 10px rgba(0,0,0,0.1)';
        } else {
            navLinks.style.display = '';
            navLinks.style.flexDirection = '';
            navLinks.style.position = '';
            navLinks.style.top = '';
            navLinks.style.left = '';
            navLinks.style.right = '';
            navLinks.style.background = '';
            navLinks.style.padding = '';
            navLinks.style.boxShadow = '';
        }
    }

    checkScreenSize();
    window.addEventListener('resize', checkScreenSize);

    // Add loading animation
    document.body.style.opacity = '0';
    setTimeout(() => {
        document.body.style.transition = 'opacity 0.5s ease';
        document.body.style.opacity = '1';
    }, 100);
});