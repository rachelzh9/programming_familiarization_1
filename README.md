# Programming familiarization Part 1

1. Write an overview of how your AI works, including how it detects where projectiles will
fall and how it chooses where to go
* The AI uses determineSafeSpots function to get an array of all safe spots that are available to move
* determineSafeSpots() does two things, first it considers each active projectile and uses the trackProjectile function to predict and update safe spots array and it also considers currently active explosions and adds it to the safe spots array
* trackProjectile() function is just using equations of motion to simulate where and when the projectile will eventually land
* Then the AI tries to move to the closest available safe spot in the safe spots array using the playerSpeed specified in the game

2. What challenges did you face when writing an AI?
* One thing I got stuck on was on realising that the explosions have a lifetime, which I wasnt considering while updating the safe spots array
* The playerSpeed variable and its description is slightly confusing since it has no units, so I introduced a bug while using it in my control function which turned medium difficulty level into impossible

3.How well does your AI work on a Hard scenario? If it doesn’t work, why? If it does, try
harder scenarios and see when it does fail and explain why
* AI works pretty well in the hard scenario but fails in the impossible scenario, one explanation that I can think off is while marking the safe spots I am considering all active projectiles but instead we can consider only the projectiles which pose an immediate danger in terms of time and only try to avoid those

4. What did you think of the assignment and did it meet its goals? Why or why not?
* Its an awesome assignment! Thanks for making us do this. It tests both the ability to read object oriented code and also make required changes to it.
