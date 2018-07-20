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
