# Prelude

This is my solution to an exam in Arduino class.

The problem with this exam was that it was way too open ended! The task was
to make SOMETHING using a Photon (which is an Arduino compatible chip with wifi capabilities)
and anything from your kit (which was a pretty standard Arduino beginner's kit).

So here I am, head in hand on the bathroom floor. It is now 1 AM- deadline is at 8- and I still
don't know what the hell to make:

Photon, photon, what to do with the photon- I really need to start right now because- CRAP! -
time is running out. Photon, photon. Just pick something, anything- photon, photon..

Eventually I decide that, "you know what, I am going to make a fucking photon!"

I don't care whether that makes sense; I am going to go to Wikipedia, learn whatever a photon is,
and that's what I'm making.

And so I did, and.. it's an interesting read that I come back to giggle at every so often.

I never did get any feedback from the teacher- it was either pass or not pass (and I did pass by the way)-
however, he allegedly asked our C teacher for help with an assignment written by "someone on LSD",
which my peers correctly assumed to be me.

The rest of this file is the original README.


# Introduction

Photons are cool, but they bear very little resemblance to actual photons
(the particle). For my exam I want to make my photon more photon like!


# Virtual

To most people, to say something is virtual means that it exists in a computer. For instance
"yesterday I played virtual soccer". Being a micro-controller, the photon is already virtual
in this sense. However, it is not a virtual particle!


Wikipedia says: "In physics, a virtual particle is a transient fluctuation that exhibits some
of the characteristics of an ordinary particle, while having its existence limited
by the uncertainty principle."


So to make my photon virtual I need to make its existence uncertain! I did this by
halting based on the result of an undecidable computation. See comments in the code for details.



# No mass

Photons (like all massless particles) have to move through space at the speed of light.
An interesting consequence of this is that they do not move through time.


Micro-controllers on the other hand very much do. In fact, their sole purpose is to
continuously transition from one state to the next as they move through time, until
they (maybe) reach some termination state.


If our micro-controller did not progress through time, then it would only ever have one
state. The most logical state to pick would be the final one, as this is the state
that the micro-controller is trying to achieve.
However, in our case the final state is undecidable because we made our photon virtual.


In order to jump to the final state without moving through all the other ones first,
we would have to perform a super computation, which is only ever possible if we
are in orbit around a black hole.


We can write a check for this:

```c
bool isInOrbit () {
  while (true);
  // We can only ever get here if we have completed an infinite amount of work
  // so we must be in orbit around a black hole!
  return true;
}
```


But this check has the unfortunate side effect that our photon can no longer
function outside of a black hole- the code blocks forever. We want to support
all spatial locations, regardless of their proximity to black holes.
Let's make a non-blocking version instead:


```c
(void*) step () { return &step; }
(void*) areWeThereYet = &step;

bool isInOrbit () {
  areWeThereYet = areWeThereYet ();
  return areWeThereYet == nullptr;
}
```


Neat. If this function ever returns true we know that we can just jump to the last state
like true photons!


We could also calculate and store Chaitin's constant here in case the user
decide to use us outside of a black hole in the future, but knowing Chaitin's constant
only allow us to solve the halting problem in finite time- our goal is zero time,
so that is useless to us. Oh well..



# Quantum entanglement

In physics, if we observe the spin of one out of a pair of entangled particles, the other one
will have the opposite spin. Before we did the observation, both particles were in a superposition.


I only have a finite number of sensors in my kit, so in the spirit of the project I decided to use
the photoresistor to detect observation, and to represent spin with a LED.


I could have the state of the LED depend on the result of an undecidable computation to simulate a
superposition, however, once the user has observed the LED I have to decide which state it should be in,
and I can neither prove the outcome of the computation that I picked, nor retroactively change my choice
without infinite energy.


Instead I just fake it and decide on the spot, which is "good enough" as the micro-controller is able
to toggle the LED faster than the human flicker fusion threshold.



# Making it useful

The photon is constantly reading the photoresistor to feed its undecidability engine.
The photoresistor could be considered a true random number generator, so we are
accumulating some high quality entropy. We might as well expose this through a
particle function.


Google has a wall of lava lamps for entropy. I have a network of photons trying
to be photons.



# Scrapped ideas

* Wave/particle duality

What does it even mean for our photon to be a wave? I don't know! Real photons
can interfere with themselves when they act like waves, so I was considering
having the photons play rock paper scissor or iterated prisoners dilemma with
each other or something, so that I could define "interacting with itself" to be
playing against itself in order to self improve, but what would the point be?


I could put up a website where you can see the photons fight against each other.
Perhaps making a betting site out of it, but now I am diverging far away from
the initial motivation of my project.
