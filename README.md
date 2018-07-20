Safari Game
-----------
Kirk A. Boyer
-------------

This is a game I made for a game programming class at the University of Denver.<br/>
The object of the game is to take photos of stuff and complete quests for NPCs by<br/>
doing so.<br/>
<br/>
The biggest challenge in making this game was to get Unreal Engine 4 to actually<br/>
capture what it was rendering to the screen unchanged (i.e. with postprocessing and<br/>
everything else, but *without* UI elements), for the "photo-taking" effect, in<br/>
such a way that the game itself had access to these photos.<br/>
<br/>
A notable feature of the game, more apparent to a developer than a player, is the<br/>
generic "pop-up" window UI element I created. It made use of UE4's built-in UI system<br/>
in a way that allowed me to create pop-ups with customizable buttons and text, and<br/>
most importantly whose buttons could *trigger events*, also in a customizable way.<br/>


Gameplay Images:
![Alt text](TitleScreen.png)
![Alt text](PhotosPauseMenuScreenshot.png)
![Alt text](ReceivingQuestScreenshot.png)


Images of Blueprint Code:
* Main Scene Blueprint
![Alt text](BlueprintScreenshots/Main_Scene_Blueprint.png)
* Blueprints within the main character's blueprint
![Alt text](BlueprintScreenshots/Main_Character_Blueprint.png)
![Alt text](BlueprintScreenshots/Death_Animation_Blueprint.png)
![Alt text](BlueprintScreenshots/Falling_Damage_Blueprint.png)
![Alt text](BlueprintScreenshots/Generic_Popup_Window_Tool_Blueprint.png)
![Alt text](BlueprintScreenshots/Quest_Handling_Blueprint.png)
![Alt text](BlueprintScreenshots/UI_Effects_and_Camera_Zoom_Blueprint.png)
