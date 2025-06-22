

// --- SETUP ---
// Using a custom sample bank for that classic drum machine feel.
samples('github:eddyflux/crate');
// Sets tempo. 0.75 cycles per second = 180 BPM. A fast, jazzy tempo.
setcps(0.75);
// Defines our lush Bbm9 -> Fm9 chord progression.
let chords = chord("<Bbm9 Fm9>/4").dict('ireal');

// --- THE STACK (All layers playing together) ---
stack(
  // --- DRUMS ---
  // The full drum kit stack with a complex, syncopated feel.
  stack(
    s("bd").struct("<[x*<1 2> [~@3 x]] x>"), // Kick drum with a variable pattern
    s("~ [rim, sd:<2 3>]").room("<0 .2>"),   // Rimshot and snare with varying reverb
    n("[0 <1 3>]*<2!3 4>").s("hh"),          // Hi-hats with a polyrhythmic feel
    s("rd:<1!3 2>*2").mask("<0 0 1 1>/16").gain(.5) // Ride cymbal appearing intermittently
  ).bank('crate')
  // This mask glitches the *entire* drum kit, creating syncopated stutters.
  .mask("<[0 1] 1 1 1>/16".early(.5)),

  // --- CHORDS ---
  // A lush electric piano playing the chord progression.
  chords.offset(-1).voicing().s("gm_epiano1:1")
  .phaser(4).room(.5),

  // --- BASSLINE ---
  // An acoustic bass following the root notes of the chords.
  n("<0!3 1*2>").set(chords).mode("root:g2")
  .voicing().s("gm_acoustic_bass"),

  // --- MELODY ---
  // An evolving, generative lead melody anchored around D5.
  chords.n("[0 <4 3 <2 5>>*2](<3 5>,8)")
  .anchor("D5").voicing()
  .segment(4).clip(rand.range(.4,.8)) // Plays short, clipped random-length notes
  .room(.75).shape(.3).delay(.25)     // Adds space, shape, and echo
  .fm(sine.range(3,8).slow(8))          // Slowly modulates the timbre with FM synthesis
  .lpf(sine.range(500,1000).slow(8)).lpq(5) // A sweeping filter for movement
  .rarely(ply("2")).chunk(4, fast(2))   // Occasionally adds fast, complex rhythms
  .gain(perlin.range(.6, .9))           // Smoothly and organically changes volume
  .mask("<0 1 1 0>/16")                 // Makes the melody rhythmically sparse
)
// --- GLOBAL GROOVE ---
// These apply a subtle human "swing" to the whole arrangement.
.late("[0 .01]*4").late("[0 .01]*2").size(4);
