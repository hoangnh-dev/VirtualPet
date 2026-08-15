<hr>

<h1 align="center">VirtualPet Development & Design Guide</h1>

<hr>

## 1. Quick getting Started
Follow the detailed setup guide here: [Getting Started Guide](https://github.com/caotrongphuoc/zomwar-game/blob/main/docs/01-guide-getting-started.md)

## 2. Game State Machine
### Screen Flow
- When no data: `Splash Screen` ➔ `Naming Screen` ➔ `Home Screen`
- When data exists: `Splash Screen` ➔ `Home Screen`
- From `Home Screen`, you can go to `Menu Screen` by up / down button
- In `Menu Screen`, you can select actions, save data, Back ➔ `Home Screen`, or select training ➔ `Training Screen`
- `Training Screen`: only time out ➔ `Home Screen`
### Pet State Logic
- **Lifecycle:** Starts as an egg ➔ hatches into a baby pet after 8s event.
- **Pet States:** Change based on time and user actions (`Idle`, `Happy`, `Dislike`, `Annoyed`, etc.).
- **Satiety / Health:** Tracked to indicate when the pet is hungry or needs sleep.
- **Growth:** Height and weight increase based on pet age.
- **Age System:** 60 seconds of playtime = 1 pet age.
- **Training:** Power increases only when trained in the `Training Screen`.
### Event Flow
- All events that change pet states are handled inside the **Pet Module**.
- Other general info is updated into the **Pet Profile Module**.
- **Screens:** Only responsible for UI logic and bitmap rendering.

> **Note:**
> 1. Pet name is set only once at the first launch.
> 2. Game data is not saved automatically; you must manually select **Save** to store progress.
