#Final Proposal

##What project you want to do
I would like to create an audio visualizer using Cinder. An audio visualizer will basically
display some sort of graphic correlating to the rhythm and tone of inputted songs. I will
probably use shapes in Cinder after analyzing the sound data to represent these effects.

##What background knowledge do you have on this kind of project, and why do you want to do this project? 
I want to do this project because I have loved music from a young age and believe it would be great
to visualize the vibrance I hear in music. I hope that it will provide a stimulating visual to others
and serve as a better representation of a song for those who may not have strong hearing and can't
hear the actual audio of a song. My background research for this project has been through Youtube
videos and stack overflows that I have found helpful and am linking here. I believe I will have to use a FFT algorithm
and spectograms to implement this.
##A rough timeline of what will get accomplished and when

###Week 1: 
First thing I need to do is learn how to process audio using cpp so I will work on implementing the FFT algorithm and
try to create a sound graph/spectogram as a beginning visual. Then I will work on setting up the necessary classes
to save certain data and use it in junction with Cinder to display visual components. If this becomes too much
for one week, I will switch over the second step to a part of Week 2.

###Week 2:
This week, I will work on the visual components and making them dynamic in a way so that they
change with every frame or update in state. I am planning on working with circles of different
sizes but would like to extend to a cooler visual such as sound bars like in a dj studio. 

###Week 3:
I will work on implementing P1 features such as making my program extensible to support
any audio inputted by the user. I will add more visual components and clean up my code as well.
I will try to add more features to make it interactive such as allowing users to choose
the shape that they want to see change or if they want an assorted/random choice made by the 
computer. I would like to essentially finish with some kind of a landscape or picture
with these shapes that changes colors and moves a bit as the music changes.

##If you were to finish the project early, what extra "stretch goals" could you implement?
###Stretch goals:
* Add more visual components rather than just changing color/size/visibility of one shape component
* Align colors to fit the moods of the song based on pitch and speed/frequency
* Allow users to speed up or slow down the song with their keyboard and adjust the audio
visualizer accordingly
