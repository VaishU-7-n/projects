let btn = document.querySelector("#btn");
let all = document.querySelector("#all");
let act = document.querySelector("#act");
let done = document.querySelector("#done");
let date = document.querySelector("#date");
let high = document.querySelector("#high");
let med = document.querySelector("#med");
let lo = document.querySelector("#lo");


all.addEventListener("click",()=>{

    let tasks = document.querySelectorAll("li");
    tasks.forEach((task)=>{task.style.display="block";});

});

act.addEventListener("click",()=>{

    let tasks = document.querySelectorAll("li");
    tasks.forEach((task)=>{
        if(task.classList.contains("done"))
        {
            task.style.display = "none";
        }
        else
        {
            task.style.display="block";
        }
        });

});

done.addEventListener("click",()=>{

    let tasks = document.querySelectorAll("li");
    tasks.forEach((task)=>{
        if(task.classList.contains("done"))
        {
            task.style.display="block";  
        }
        else
        {
            task.style.display = "none"; 
        }
        });

});

btn.addEventListener("click",()=>{

    let val = document.querySelector("#val")
    let str = val.value;
    str = str + "     " + date.value;

    let elem = document.createElement("li");
    elem.innerHTML = str;

    
    
    
   let check = document.querySelector("#opt").value;
   if(check==="Low")
    lo.append(elem);
   else if(check === "Medium")
    med.append(elem);
   else
    high.append(elem);
    
    elem.addEventListener("click", () => {
        elem.style.textDecoration = "line-through";
        elem.classList.add("done");
    });

    let del = document.createElement("button");
    del.innerHTML="delete";
    elem.appendChild(del);

    del.addEventListener("click", () => {
        elem.remove();
    });

    val.value = "";
   

});


