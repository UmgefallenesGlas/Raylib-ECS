# Documantations
<br>

## Setup
Just add The folder to your Source Files and do in your main/game file
```
#include "ECS/Components.h"
```
To use the features use
```
Manager manager;
```
in your file where you included it

## Entitys
Create an Entity with
```
auto& myEntity = manager.addEntity();
```
### Add Components
in your start function with 
```
myEntity.addComponent<TransformComponent>();
```

# Components
``` 
Transform Component
Sprite Component
Animated Sprite Component
```
