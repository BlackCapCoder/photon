#include "util.h"
#include <stddef.h>
#include <limits.h>

#define universeDecayRate 500
#define sexualDeprivation 60000

/* Hello, future blackcap here.

   Yes- I absolutely did that on purpose!

   The sole purpose of having those variables is
   so that the first thing teach reads is
   "universeDecayRate" and "sexualDeprivation".
*/

constexpr int pin_spin   = D0;
constexpr int pin_pr_inp = A0;
constexpr int pin_pr_pwr = A5;

unsigned darkness, tolerance;


// turing machine used to generate undecidability
ID<unsigned short> undecidability { 1024 };

void stepUndec (unsigned short sample)
{
  undecidability.step (sample % 2);
  if (undecidability.isHalt()) exit (EXIT_SUCCESS); // Actually causes the particle to reboot
}

// We expose this through a particle function
unsigned short getEntropy (String)
{
  unsigned short ret = undecidability.mem[0];
  for (int i = 1; i < undecidability.size; i++)
    ret ^= undecidability.mem[i];
  return ret;
}


/* Hi- future cap' again!

   So here's the setup:

   We have this photon chip, with a photoresistor and a singular LED hooked up to it-
   which I imagine that the user now places in a box.

   While in the box, the state of the LED is undefined- IE: in a superposition-
   but the moment he opens the box we have to decide on a state.

   Up next I implement a dating hub for finding a partner (that's the entanglement),
   and if either chip is observed (IE: we open the box), the other
   has to pick the opposite state.

   The code is perfectly boring so skip it if you'd like.
*/


// We may or may not be entangled to another photon
char * entangled = nullptr;
char myName [16];

// There is an entanglement hub where photons can request entanglement.
// Unless we are already entangled, bite!
void entangleHub (const char *, const char * who)
{
  if (entangled != nullptr) return;
  Particle.publish ("Quantum_Entanglement_" + String(who), myName, PUBLIC);
}

// Oh la-la, she's into us!
void entanglePrivate (const char *, const char * who)
{
  if (entangled != nullptr) return;
  int len = strlen(who);

  entangled = new char[len];
  memcpy (entangled, who, len);

  Particle.publish ("Quantum_Entanglement_" + String(entangled), myName, PUBLIC);
}


// A spin that could be in a superposition
long timeSpinUpdated = LONG_MIN;
bool * spin = nullptr;

void onSpinUpdated ()
{
  if (spin == nullptr) return;
  digitalWrite (pin_spin, *spin);
  timeSpinUpdated = millis ();
}

// We're caught!
void onObserve ()
{
  if (spin != nullptr) return;
  spin = new bool;
  *spin = rand() % 2;
  onSpinUpdated();

  if (entangled == nullptr) return;

  char msg[17];
  memcpy(msg+1, myName, 16);
  msg[0] = !spin ? '1' : '0';

  Particle.publish ("Quantum_Entanglement_Collapse_" + String(entangled), msg, PUBLIC);
}

// Partner caught :(
void entagledCollapsed (const char *, const char * msg)
{
  if (entangled == nullptr) return;
  if (spin != nullptr) return;
  if (strcmp(msg+1, entangled) != 0) return;

  spin  = new bool;
  *spin = msg[0] == '1';
  onSpinUpdated();
}

// Find a partner
long lastMingle = -1;
void mingle ()
{
  if (entangled != nullptr) return;
  if (spin      != nullptr) return;

  long now = millis ();

  if (now - lastMingle < sexualDeprivation) return;

  lastMingle = now;
  Particle.publish ("Quantum_Entanglement", myName, PUBLIC);
}


void setup ()
{
  pinMode      (pin_spin,   OUTPUT);
  pinMode      (pin_pr_inp, INPUT);
  pinMode      (pin_pr_pwr, OUTPUT);
  digitalWrite (pin_pr_pwr, HIGH);
  /* digitalWrite (pin_spin, HIGH); */


  // Calibrate photoresistor. We assume that it is dark
  {
    #define NUM_SAMPLES 100

    unsigned short min = USHRT_MAX;
    unsigned short max = 0;
    long sum = 0;


    for (int i = 0; i < NUM_SAMPLES; i++) {
      unsigned short s = analogRead (pin_pr_inp);
      min = min < s ? min : s;
      max = max > s ? max : s;
      sum += s;
      delay (1);
    }

    unsigned short avg = sum / NUM_SAMPLES;

    tolerance  = (unsigned) (max - min) / 2;
    darkness   = (unsigned) avg;
    /* darkness   = (unsigned) min; */
    /* tolerance  = tolerance/10; */
    /* tolerance += (tolerance * 10)/9; // allow 10% deviation */
  }

  // Quantum entanglement
  {
    for (int i = 0; i < 15; i++)
      myName[i] = 'a' + (rand() % 26);
    myName[15] = 0;

    Particle.subscribe ("Quantum_Entanglement_" + String(myName), entanglePrivate);
    Particle.subscribe ("Quantum_Entanglement_Collapse_" + String(myName), entagledCollapsed);
    Particle.subscribe ("Quantum_Entanglement", entangleHub);
  }

  Particle.function("entropy", getEntropy);
  Serial.begin(9600);
}


void loop ()
{
  unsigned short sample = analogRead (pin_pr_inp);

  // The photoresistor reading should be somewhat random, so we can
  // treat this as our program.
  stepUndec (sample);

  // If we are capable of super computation, just run this to completion.
  // "But you are not resampeling!", you might say. We are in a black hole remember? There is no light!
  while (Super::check()) stepUndec (sample);

  // Are we being observed?

  Serial.print(sample);
  Serial.print(", ");
  Serial.print(darkness);
  Serial.print(", ");
  Serial.println(tolerance);
  if (sample > darkness + tolerance) onObserve ();

  mingle ();

  // They probably forgot our spin already- let's enter a super position-
  // let's raise the entropy of the universe, one bit at a time! Muahahaha!
  if (spin != nullptr && millis() - timeSpinUpdated > universeDecayRate) {
    delete spin;
    spin = nullptr;
  }
}
