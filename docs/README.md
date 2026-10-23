First Week Milestone Standup
End of Week Standup. 
For my design process, I largely look at a macro picture first, then dive into what's need to make the big picture work. So I started with making a text based adventure, and then broke it out into what I would need, such as, Characters, combat system, core game loop, lore, item/inventory, etc...

So far, this week I completed my menu system with one exception, my new game will initialize my game loop. Load game is not complete yet as I have not added a save/load system yet. I have a fully functional "how to play" section. My Lore Menu option will take you to another Lore Menu and I have given tidbits of lore about the world, playable characters, locations, and a beastiary. I have also completed the credits, and exit game functionality.

Part of what I also have added is input validation. 

Currently I am working on my character class for the two characters, so I can begin expanding the game loop.

My biggest stumbling block this week has come in with writing the getters/setters inside my character class. It's something i should've spent more time on in PG1 and PG2 and I have spent A LOT of time in Geeks4Geeks making sure I have them up and running correctly. 

My big goal with the remainder of time I have this week will be to fleshing out the character class and then begin digging into my enemy class so that I can begin the combat system this week. 


END OF WEEK STANDUP. 

Well, as far as work this week. I was able to finalize the game. Once I wrapped up the currency and item management system on Monday/Tuesday I was able to finish the ability and combat system Wednesday and Thursday, then I jumped into polishing and using console colors and the like to make it prettier. 

I finished/polished everything in the game. There's a few things I didn't get to add that would have made the game a little more player friendly, like a leveling system, and for turn based I was trying to work on a reactive combat system similar to Legend of Dragoon or Expedition 33. If I have time to tweak it today I will.  One big thing I did refactor was my Game.cpp, Game isn't my main, it controlled my game loop and gameplay. While Main is VERY clean, game.cpp is not.  Before yesterday, I had many of my story elements out of order as I worked on them at different times over the month. I spent a good bit of time yesterday reordering them so that they would at least read in a logical order. 

Challenges: The biggest thing I ran into this week was time. I might have tried to take on a larger project than I should have for the month. I was fine at first, but missing three days last week due to being sick got me far behind where I wanted to be. That said, I got through the time crunch by working on this project alongside my day job. 

I needed this month. I'm a hands on learner. Having a month to be turned loose to work on a project of my choosing helped SO much.

I am going to continue this project. I've had project ADHD the past couple of months. Started a few game ideas in my free time but keep jumping between them. I planned and wrote this project so I could be flexible and move it into the larger project. So I am fully planning on letting this be the framework to the larger project that I will begin likely this weekend.