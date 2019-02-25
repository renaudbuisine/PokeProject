# Game Object

Main part of the library.

## Roles

- Owns the dependencies injector
- Create scenes
- Handle the scenes stack
- Handle the asynch tasks life cycle (run - complete - remove from stack)

## Life Cycle

- Basic functions

```cpp
/**
Launch loop
*/
void run(void);

/**
Pause the loop
*/
void pause(void) noexcept;
/**
Resume the loop
*/
void resume(void) noexcept;

/**
Stop the loop (unload resources)
*/
void stop(void) noexcept;
```

- Other actions
- - At each inner update (every 30ms), inner update function or each running scene is called
- - At each update, update function or each running scene is called
- - At each update, update function of each task is called
- - Manage scenes transitions

## Required functions

The load function is not automatically called, needs calling if elements really need loading (**the first scene for example!**).

```cpp
/**
Load initial components of game - Needs calling - Synchrone function by default
(needs overriding)
*/
virtual void load(void) noexcept = 0;
```

Following functions are called during main code life cycle. They can be empty, just fill with specific behaviors.

```cpp

//Updates
/**
called a each loop whatever elapsedtimestamp value
(needs override)

@param elapsedTimestamp elapsed time stamp (in seconds)
*/
virtual void update(const float elapsedTimestamp) = 0;
/**
called 30 times a second
(needs override)
*/
virtual void fixedUpdate(void) = 0;
```

## Callbacks

**Should be used by UI layer!**

- updateCallBack: Called when at any update, at each main loop
- fixedUpdateCallBack: Called every 30ms
- addSceneCallBack: Called when the transition to the scene is over and scene becomes the main one
- removeSceneCallBack: Called when a scene is not part of the managed stack anymore, resources can be released

# Scene Object

## Life Cycle

- Basic functions

```cpp
//Loading
virtual void load(void) noexcept = 0;

//Updates
/**
called a each loop whatever elapsedtimestamp value

@param elapsedTimestamp elapsed time stamp (in seconds)
*/
virtual void update(const float elapsedTimestamp) noexcept = 0;
/**
called 30 times a second
*/
virtual void fixedUpdate(void) noexcept = 0;

// Controls
virtual void addControl(std::weak_ptr<rpg_control>) noexcept = 0;
```

- Add control: used to add a control (touch screen, etc.. to scene)

```cpp
// Controls
virtual void addControl(std::weak_ptr<rpg_control>) noexcept = 0;
```

## Callbacks

**Should be used by UI layer!**

- loadResourcesCallback: Called to load all resources

# Router Object

## Life cycle

```cpp
//LOADING
virtual bool prepareScene(void) noexcept = 0;

//TRANSITIONING
bool transitionFromScene(std::shared_ptr<rpg_scene>) noexcept;
```

## Callbacks

- transitionFromToSceneCallback: Called to animate transition between two scenes

## Delegate

```cpp
/**
When scene is loaded
*/
virtual void didLoad(void) noexcept = 0;
/**
When transition to new scene is done
*/
virtual void didEndTransition(void) noexcept = 0;
```

# Asynch task

Build a new task:
```cpp
std::shared_ptr<rpg_asyncTask> task(new rpg_asyncTask([&]{
    //Long code
    for(int i = 0; i < 1000000; i++);
}));
```
Once it is build, set the delegate:
```cpp
task->setDelegate(this)
```
Only a game object can run a asynch task:
```cpp
game->runTask(task)
```
Several tasks can be running in the same time, the game object is running through each one at each loop, once one is over, the
```cpp
task->isCompleted
```
is true, the delegate function didCompleteTask is called. Then the task is removed from the game object.

# Load a new scene
