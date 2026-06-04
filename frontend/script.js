// ======================================================
// BUTTONS
// ======================================================

let btn = document.querySelector("#btn");

let all = document.querySelector("#all");
let act = document.querySelector("#act");
let done = document.querySelector("#done");



// ======================================================
// INPUTS
// ======================================================

let date = document.querySelector("#date");



// ======================================================
// PRIORITY SECTIONS
// ======================================================

let high = document.querySelector("#high");
let med = document.querySelector("#med");
let lo = document.querySelector("#lo");



// ======================================================
// LOAD TODOS FROM BACKEND
// ======================================================

async function loadTodos()
{
    let res = await fetch("http://127.0.0.1:8000/todos");

    let todos = await res.json();

    todos.forEach((todo) => {

        createTask(todo);

    });
}


// load when page opens
loadTodos();



// ======================================================
// CREATE TASK UI
// ======================================================

function createTask(todo)
{
    // create li
    let elem = document.createElement("li");



    // ======================================================
    // TASK TEXT
    // ======================================================

    let text = document.createElement("span");

    text.innerHTML =
    `${todo.text} &nbsp;&nbsp; ${todo.due_date}`;

    elem.appendChild(text);



    // ======================================================
    // IF ALREADY COMPLETED
    // ======================================================

    if(todo.completed)
    {
        elem.classList.add("done");
    }



    // ======================================================
    // APPEND TO CORRECT PRIORITY SECTION
    // ======================================================

    if(todo.priority === "Low")
    {
        lo.append(elem);
    }
    else if(todo.priority === "Medium")
    {
        med.append(elem);
    }
    else
    {
        high.append(elem);
    }



    // ======================================================
    // TOGGLE DONE
    // ======================================================

    elem.addEventListener("click", async () => {

        // toggle class visually
        elem.classList.toggle("done");


        // update backend
        await fetch(
            `http://127.0.0.1:8000/todos/${todo.id}`,
            {
                method: "PUT"
            }
        );

    });



    // ======================================================
    // DELETE BUTTON
    // ======================================================

    let del = document.createElement("button");

    del.innerHTML = "delete";

    elem.appendChild(del);



    // ======================================================
    // DELETE TASK
    // ======================================================

    del.addEventListener("click", async (e) => {

        // stop li click
        e.stopPropagation();


        // delete from backend
        await fetch(
            `http://127.0.0.1:8000/todos/${todo.id}`,
            {
                method: "DELETE"
            }
        );


        // remove from UI
        elem.remove();

    });

}



// ======================================================
// ADD TASK
// ======================================================

btn.addEventListener("click", async () => {

    let val = document.querySelector("#val");

    let check = document.querySelector("#opt").value;



    // prevent empty tasks
    if(val.value.trim().length === 0)
    {
        return;
    }



    // create todo object
    let todo = {

        text: val.value,

        priority: check,

        due_date: date.value,

        completed: false

    };



    // send to backend
    let res = await fetch(
        "http://127.0.0.1:8000/todos",
        {

            method: "POST",

            headers: {
                "Content-Type": "application/json"
            },

            body: JSON.stringify(todo)

        }
    );



    // get saved todo
    let data = await res.json();



    // add to UI
    createTask(data);



    // clear input
    val.value = "";

});



// ======================================================
// SHOW ALL
// ======================================================

all.addEventListener("click", () => {

    let tasks = document.querySelectorAll("li");

    tasks.forEach((task) => {

        task.style.display = "flex";

    });

});



// ======================================================
// SHOW ACTIVE
// ======================================================

act.addEventListener("click", () => {

    let tasks = document.querySelectorAll("li");

    tasks.forEach((task) => {

        if(task.classList.contains("done"))
        {
            task.style.display = "none";
        }
        else
        {
            task.style.display = "flex";
        }

    });

});



// ======================================================
// SHOW DONE
// ======================================================

done.addEventListener("click", () => {

    let tasks = document.querySelectorAll("li");

    tasks.forEach((task) => {

        if(task.classList.contains("done"))
        {
            task.style.display = "flex";
        }
        else
        {
            task.style.display = "none";
        }

    });

});
