const apiUrl = "https://www.themealdb.com/api/json/v1/1/search.php";
const randomMealUrl = "https://www.themealdb.com/api/json/v1/1/random.php";

document.getElementById("searchButton").addEventListener("click", searchRecipes);
document.getElementById("randomMealButton").addEventListener("click", getRandomMeal);

function searchRecipes() {
    const foodName = document.getElementById("foodInput").value;
    const ingredients = document.getElementById("ingredientsInput").value.split(",");

    if (!foodName.trim()) {
        showErrorMessage("Please enter a food name");
        return;
    }

    const url = `${apiUrl}?s=${foodName}`;

    fetch(url)
        .then(response => response.json())
        .then(data => {
            if (data.meals) {
                displayRecipes(data.meals);
                displayCategories(data.meals);
            } else {
                showErrorMessage("No recipes found.");
            }
        })
        .catch(error => {
            showErrorMessage("Error fetching recipes. Please try again.");
            console.error(error);
        });
}

function getRandomMeal() {
    fetch(randomMealUrl)
        .then(response => response.json())
        .then(data => {
            if (data.meals) {
                displayRecipes(data.meals);
            } else {
                showErrorMessage("No random meal found.");
            }
        })
        .catch(error => {
            showErrorMessage("Error fetching random meal. Please try again.");
            console.error(error);
        });
}

function displayRecipes(meals) {
    const recipesDiv = document.getElementById("recipes");
    recipesDiv.innerHTML = ""; // Clear previous results

    meals.forEach(meal => {
        const recipeElement = document.createElement("div");
        recipeElement.classList.add("recipe");

        const recipeTitle = document.createElement("h3");
        recipeTitle.textContent = meal.strMeal;
        recipeElement.appendChild(recipeTitle);

        const mealImage = document.createElement("img");
        mealImage.src = meal.strMealThumb;
        mealImage.alt = meal.strMeal;
        mealImage.classList.add("meal-thumbnail");
        recipeElement.appendChild(mealImage);

        const recipeDescription = document.createElement("p");
        recipeDescription.textContent = meal.strInstructions || "No instructions available.";
        recipeElement.appendChild(recipeDescription);

        const ingredientsList = document.createElement("ul");
        for (let i = 1; i <= 20; i++) {
            if (meal[`strIngredient${i}`] && meal[`strMeasure${i}`]) {
                const ingredientItem = document.createElement("li");
                ingredientItem.textContent = `${meal[`strIngredient${i}`]} - ${meal[`strMeasure${i}`]}`;
                ingredientsList.appendChild(ingredientItem);
            }
        }
        recipeElement.appendChild(ingredientsList);

        const category = document.createElement("p");
        category.textContent = `Category: ${meal.strCategory}`;
        recipeElement.appendChild(category);

        const area = document.createElement("p");
        area.textContent = `Area: ${meal.strArea}`;
        recipeElement.appendChild(area);

        recipesDiv.appendChild(recipeElement);
    });
}

function displayCategories(meals) {
    const categoryListDiv = document.getElementById("categoryList");
    categoryListDiv.innerHTML = ""; // Clear previous categories

    // Collect all unique categories
    const categories = new Set();
    meals.forEach(meal => {
        if (meal.strCategory) {
            categories.add(meal.strCategory);
        }
    });

    categories.forEach(category => {
        const categoryElement = document.createElement("div");
        categoryElement.textContent = category;
        categoryListDiv.appendChild(categoryElement);
    });
}

function showErrorMessage(message) {
    const errorDiv = document.getElementById("errorMessage");
    errorDiv.textContent = message;
    errorDiv.style.color = "red";
}
