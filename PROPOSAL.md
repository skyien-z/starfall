####Starfall

#####Proposal
The stars have long held my imagination, and from the amount of references 
to them in both literature and popular culture, I can conclude the stars 
have long held our collective human imagination. Thus, I will
 develop a creative rendering of shooting stars for my final project. The
 final app will be interactive and contain both audio and visual components 
 (described in greater detail in the timeline section below).
 
#####Background
I am no astronomer, so the science behind shooting stars eludes me.
However, I am an avid consumer of fantasy books, so I love all sorts of
imagery. In particular, I adore a scene describing "Starfall," a shooting star
 festival, in *A Court of Mist and Fury* by Sarah J. Maas. The scene is excerpted
 below and edited for concision: 

> Another star crossed the sky, twirling and twisting over itself, as if it were reveling in its own sparkling beauty. It was chased by another, and another, until a brigade of them were unleashed from the edge of the horizon, like a thousand archers had loosed them from mighty bows.
 The stars cascaded over us, filling the world with white and blue light. They were like living fireworks, and my breath lodged in my throat as the stars kept on falling and falling. 
 I’d never seen anything so beautiful.
>
> 
> “There must be hundreds of them,” I managed to say, 
dragging my stare back to the stars whizzing past.
> 
> “Thousands,” he said. “They’ll keep coming until dawn. Or, I hope they will. 
 There were less and less of them the last time I witnessed Starfall.”
> 
> “What’s happening to them?”
> 
> “I wish I knew. But they keep coming back despite it.”
> 
> “Why?”
> 
> “Why does anything cling to something? Maybe they love wherever they’re going so much that it’s worth it. Maybe they’ll keep coming back, until there’s only one star left. 
 Maybe that one star will make the trip forever, out of the hope that someday––if it keeps coming back often enough––another star will find it.” 
>
>
>
> *MLA Citation: Maas, Sarah J. A Court of Mist and Fury. Bloomsbury, 2016.*

#####Timeline
Week 1:
* Render a starry sky background using Cinder
   1. Either hand-draw and import background image or use Cinder's functionality 
    to draw background (should have mountains in the distance for the foreground)
* Render a single shooting star on Cinder
    1. Star must follow linear trajectory (equation variables can be hard coded in for this week)
    2. Star must have a "head" that is a very bright color and be surrounded by a darker hue
    of that same color
    3. Once the head passes a place, a bright streak of color must be left behind to 
    gradually darken and fade by a timer in order to create a comet effect
    4. Stars must not enter foreground and must disappear behind mountains

Week 2:
* Add user interaction
    1. Allow user to set slope of trajectory
    2. Allow user to click on night image to create a new shooting star where clicked
    3. Allow user to set color of shooting star
    4. Allow users to create any number of shootings stars in background
* Add background music to app

Week 3: 
* Create action that "pre-loads" a random color and random slope for a shooting
 star that user can click to release
* Enable star color blending if stars or their tails overlap
* Add Starfall Scene Paragraph
    1. Sentences of the paragraph excerpted should fade in and out by a timer

#####Stretch Goals
* Create a complete automatic animation of Starfall
    1. Automatic animation should follow description of shooting stars in excerpt
    2. User can choose to play this pre-loaded animation or create their own stars
    
      
* Release stars based on audio input (Very Distant Goal)
    1. A faster song will release more stars than a slow song
    2. A major key will release warm-colored stars
    3. A minor key will release cool-colored stars


* Release stars based on MIDI input (Very Very Distant Goal)
    1. Release stars based on real-time audio input from a MIDI device