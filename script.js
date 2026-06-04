// buttons
let btn = document.querySelector("#btn");

let all = document.querySelector("#all");
let act = document.querySelector("#act");
let done = document.querySelector("#done");


// inputs
let date = document.querySelector("#date");


// priority sections
let high = document.querySelector("#high");
let med = document.querySelector("#med");
let lo = document.querySelector("#lo");

async function loadTodos()
{
    let res = await fetch("http://127.0.0.1:8000/todos");

    let todos = await res.json();

    todos.forEach((todo) => {

        createTask(todo);

    });
}

loadTodos();

function createTask(todo) {
    // create li
    let elem = document.createElement("li");



    // task text
    let text = document.createElement("span");

    text.innerHTML = `${todo.text} &nbsp;&nbsp; ${todo.date}`;

    elem.appendChild(text);



    // if completed before refresh
    if (todo.completed) {
        elem.classList.add("done");
    }



    /* ======================================================
       APPEND TO CORRECT PRIORITY SECTION
    ====================================================== */

    if (todo.priority === "Low") {
        lo.append(elem);
    }
    else if (todo.priority === "Medium") {
        med.append(elem);
    }
    else {
        high.append(elem);
    }



    /* ======================================================
       TOGGLE DONE
    ====================================================== */

    elem.addEventListener("click", () => {

        elem.classList.toggle("done");

        todo.completed = !todo.completed;

    });



    /* ======================================================
       DELETE BUTTON
    ====================================================== */

    let del = document.createElement("button");

    del.innerHTML = "delete";

    elem.appendChild(del);



    del.addEventListener("click", (e) => {

        // stop li click
        e.stopPropagation();

        // remove from UI
        elem.remove();

        // remove from array
        todos = todos.filter((t) => t !== todo);


    });

}



/* ======================================================
   LOAD SAVED TASKS
====================================================== */

todos.forEach((todo) => {

    createTask(todo);

});



/* ======================================================
   ADD TASK
====================================================== */

btn.addEventListener("click", () => {

    let val = document.querySelector("#val");

    let check = document.querySelector("#opt").value;



    // prevent empty tasks
    if (val.value.trim().length === 0) {
        return;
    }



    // create object
    let todo = {

        text: val.value,

        date: date.value,

        priority: check,

        completed: false

    };

    // add to array
    todos.push(todo);

    // show in UI
    createTask(todo);

    // clear input
    val.value = "";

});



/* ======================================================
   SHOW ALL
====================================================== */

all.addEventListener("click", () => {

    let tasks = document.querySelectorAll("li");

    tasks.forEach((task) => {

        task.style.display = "flex";

    });

});



/* ======================================================
   SHOW ACTIVE
====================================================== */

act.addEventListener("click", () => {

    let tasks = document.querySelectorAll("li");

    tasks.forEach((task) => {

        if (task.classList.contains("done")) {
            task.style.display = "none";
        }
        else {
            task.style.display = "flex";
        }

    });

});



/* ======================================================
   SHOW DONE
====================================================== */

done.addEventListener("click", () => {

    let tasks = document.querySelectorAll("li");

    tasks.forEach((task) => {

        if (task.classList.contains("done")) {
            task.style.display = "flex";
        }
        else {
            task.style.display = "none";
        }

    });

});