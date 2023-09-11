let button_pick = document.querySelector("#button")
console.log(typeof button_pick)

let counter = 0
function result(){
    ++counter
    let but_res = document.querySelector("#headder")
    but_res.innerHTML = "Количество нажатий: " + counter

    let button_couner = document.querySelector("#main_text")
    // if (counter % 3 == 0) {
    //     button_couner.innerHTML = "Страница 3:"
    // } else if (counter % 2 == 0) {
    //     button_couner.innerHTML = "Страница 2:"
    // } else if (counter % 1 == 0) {
    //     button_couner.innerHTML = "Страница 1:"
    // }

    switch (counter % 3) {
        case 0:
            button_couner.innerHTML = "Страница 3:"
            button_couner.style.color = "pink"
            button_couner.style.backgroundColor = "red"
            break;
        case 1:
            button_couner.innerHTML = "Страница 1:"
            button_couner.style.color = "limegreen"
            button_couner.style.backgroundColor = "darkgreen"
            break;
        case 2:
            button_couner.innerHTML = "Страница 2:"
            button_couner.style.color = "aquamarine"
            button_couner.style.backgroundColor = "darkBlue"
            break;
    }

    // button_couner.innerHTML = site_stages[counter % 3]
}

// var site_stages = {
//     0: "Страница 3",
//     1: "Страница 1",
//     2: "Страница 2", 
// }
// var site_stages = ["Страница 3", "Страница 1", "Страница 2"]


button_pick.addEventListener("click", result) // Добавить слушатель событий