from fastapi import FastAPI
from database import engine
from models import Base
from database import SessionLocal
from sqlalchemy.orm import Session
from fastapi import Depends
from models import Todo
from fastapi.middleware.cors import CORSMiddleware

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

Base.metadata.create_all(bind=engine)

def get_db():

    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()



@app.get("/todos")
def get_todos(db: Session = Depends(get_db)):
    todos = db.query(Todo).all()
    return todos

@app.get("/todos/active")
def get_act(db: Session = Depends(get_db)):
    todos = db.query(Todo).filter(Todo.completed == False).all()
    return todos

    
@app.get("/todos/done")
def get_done(db: Session = Depends(get_db)):
    todos = db.query(Todo).filter(Todo.completed == True).all()
    return todos

@app.post("/todos")
def create_todo(todo: dict, db: Session = Depends(get_db)):

    new_todo = Todo(

        text=todo["text"],

        priority=todo["priority"],

        due_date=todo["due_date"],

        completed=todo["completed"]

    )

    db.add(new_todo)

    db.commit()

    db.refresh(new_todo)

    return new_todo

@app.put("/todos/{id}")
def modify_todo(id: int, db: Session = Depends(get_db)):
    todo = db.query(Todo).filter(Todo.id == id).first()

    if(todo is None):
        return {"message": "Todo not found"}
    todo.completed = not todo.completed
    db.commit()
    db.refresh(todo)
    return todo

@app.delete("/todos/{id}")
def delete_todo(id: int, db: Session = Depends(get_db)):
    todo = db.query(Todo).filter(Todo.id == id).first()

    if(todo is None):
        return {"message": "Todo not found"}
    
    db.delete(todo)
    db.commit()
    return {"message": "Todo deleted"}


