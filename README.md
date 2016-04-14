Mimic, the Mycroft TTS Engine
==============================

[![Stories in Ready](https://badge.waffle.io/MycroftAI/mimic.png?label=ready&title=Ready)](https://waffle.io/MycroftAI/mimic)
[![Build Status](https://travis-ci.org/MycroftAI/mimic.svg?branch=development)](https://travis-ci.org/MycroftAI/mimic)
[![codecov.io](https://codecov.io/github/MycroftAI/mimic/coverage.svg?branch=development)](https://codecov.io/github/MycroftAI/mimic?branch=development)
[![Coverity Scan](https://img.shields.io/coverity/scan/8420.svg)](https://scan.coverity.com/projects/mycroftai-mimic?tab=overview)

Mimic is a lightweight run-time speech synthesis engine, based on
Flite (Festival-Lite). The Flite project website can be found
here: http://www.festvox.org/flite/ - further information can be found
in the ACKNOWLEDGEMENTS file in the Mimic repo.

### Requirements:

An audio device and audio libraries aren't strictly required as mimic can write
its output to a waveform file. However they are included in requirements for
their convenience.


#### Linux

- A good C compiler. gcc or clang are fine.
- GNU make
- pkg-config
- For audio output: either ALSA, PortAudio or PulseAudio headers. We recommend
  ALSA output for greater compatibility with most setups.

On a Debian/Ubuntu computer this can be installed by using:

    sudo apt-get install gcc make pkg-config libasound2-dev

#### Mac OSX

- A good C compiler. gcc or clang are fine.
- GNU make
- pkg-config
- PortAudio

In order to install pkg-config and PortAudio, `brew` can be used:

1. Install brew

    /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

2. Install pkg-config and PortAudio

    brew install pkg-config portaudio

#### Windows

* A good C compiler, some of these files are quite large and some C
  compilers might choke on these, gcc is fine. Visual C++ 6.0 is known to fail
  on the large diphone database files.  We recommend you use GCC under Cygwin
  or mingw32 instead.
* GNU Make
* PortAudio


### Supported platforms:

We have successfully compiled and run on

- Linux, with both ARM and Intel architectures under it
- Mac OS X
- Android

### Building mimic

1. Clone the repository (or download a tarball)

    git clone https://github.com/MycroftAI/mimic.git

2. Navigate to the mimic directory

    cd mimic

3. Configure.

    ./configure

4. Build:

    make
 
Note: When rebuilding, often you will only need to run `make`.
If you make changes to compile flags you will probably want to
run `make clean` before recompiling with `make`.

###Usage:

    TODO: Shorten and update this to reflect current process,
    update relevant filenames.

The `./bin/mimic` voices contains all supported voices and you may
choose between the voices with the `-voice` flag and list the supported
voices with the `-lv` flag.  Note the kal (diphone) voice is a different
technology from the others and is much less computationally expensive
but more robotic.  For each voice additional binaries that contain
only that voice are created in ./bin/mimic_FULLVOICENAME,
e.g. `./bin/mimic_cmu_us_awb`.

If it compiles properly a binary will be put in `bin/`, note by
default `-g` is on so it will be bigger than is actually required

   `./bin/mimic "Flite is a small fast run-time synthesis engine" mimic.wav`

Will produce an 8KHz riff headered waveform file (riff is Microsoft's
wave format often called .WAV).

   `./bin/mimic doc/alice`

Will play the text file doc/alice.  If the first argument contains
a space it is treated as text otherwise it is treated as a filename.
If a second argument is given a waveform file is written to it,
if no argument is given or "play" is given it will attempt to
write directly to the audio device (if supported).  if "none"
is given the audio is simply thrown away (used for benchmarking).
Explicit options are also available.

   `./bin/mimic -v doc/alice none`

Will synthesize the file without playing the audio and give a summary
of the speed.

   `./bin/mimic doc/alice alice.wav`

will synthesize the whole of alice into a single file (previous
versions would only give the last utterance in the file, but
that is fixed now).

An additional set of feature setting options are available, these are
*debug* options, Voices are represented as sets of feature values (see
`lang/cmu_us_kal/cmu_us_kal.c`) and you can override values on the
command line.  This can stop mimic from working if malicious values
are set and therefore this facility is not intended to be made
available for standard users.  But these are useful for
debugging.  Some typical examples are

`./bin/mimic --sets join_type=simple_join doc/intro.txt`
     Use simple concatenation of diphones without prosodic modification

`./bin/mimic -pw doc/alice`
     Print sentences as they are said

`./bin/mimic --setf duration_stretch=1.5 doc/alice`
     Make it speak slower

`./bin/mimic --setf int_f0_target_mean=145 doc/alice`
     Make it speak higher

The talking clock is an example talking clode as discussed on
http://festvox.org/ldom it requires a single argument HH:MM
under Unix you can call it
    ``./bin/mimic_time `date +%H:%M` ``

`./bin/mimic -lv`
    List the voices linked in directly in this build

`./bin/mimic -voice rms -f doc/alice`
    Speak with the US male rms voice

`./bin/mimic -voice awb -f doc/alice`
    Speak with the "Scottish" male awb voice

`./bin/mimic -voice slt -f doc/alice`
    Speak with the US female slt voice


`./bin/mimic -voice http://www.festvox.org/flite/packed/flite-2.0/voices/cmu_us_ksp.flitevox -f doc/alice`
    Speak with KSP voice, download on the fly from festvox.org

`./bin/mimic -voice voices/cmu_us_ahw.mimicvox -f doc/alice`
    Speak with AHW voice loaded from the local file.

Voice names are identified as loadable files if the name includes a
"`/`" (slash) otherwise they are treated as internal names.  So if you
want to load voices from the current directory you need to prefix them
with "`./`".

###Voices

TODO: Explain where to find voices, and how to obtain new ones.

The `voices/` directory contains several flitevox voices.

You can also find existing Flite voices here:
  `http://www.festvox.org/flite/packed/flite-2.0/voices/`

###Debugging:

  The debug flag `-g` is already set when compiling. (This should
  probably be removed on release build)

  Note: Currently the configure script enables compiler optimizations.
  These optimizations are the reason for any weird behavior while
  stepping through the code. (Due to the fact that the compiler has
  reordered/removed many lines of code.) 

  For now to disable optimizations edit the file `mimic/config/config`
  by hand. Near the top of the file change: `CFLAGS   = -g -O2 -Wall`
  to read: `CFLAGS   = -g -O0 -Wall`
  (You can also put any other debug flags here that you wish)
  Keep in mind that this file is auto generated by the `configure`
  script and will be overwritten if the script is run.
  Run `make clean` and then `make` to rebuild with the new flags.

  Now you can run the program in the debugger:
  `gdb --args ./bin/mimic -t "Hello. Doctor. Name. Continue. Yesterday. Tomorrow."`
  
###How to Contribute 
  For those who wish to help contribute to the development of mimic
  there are a few things to keep in mind. 
  
#####Git branching structure
  We will be using a branching struture similar to the one described in this article:
  http://nvie.com/posts/a-successful-git-branching-model/ (a very interesting read)
  
  In short:
  
  `master` branch is for stable releases, 
  
  `development` branch is where development work is done between releases,
  
  any feature branch should branch off from `development`, and when complete will be merged back into `development`.
  
  Once enough features are added or a new release is complete those changes in `development` will be merged into `master`, 
  then work can continue on `development` for the next release. 
  
##### Coding Style Requirements
  To keep the code in mimic coherent a simple coding style/guide is used. It should be noted that the current codebase as a whole does not meet some of these guidlines,this is a result of comming from the flite codebase. As different parts of the codebase are touched it is the hope that these inconsistancies will deminish as time goes on.

  **Indentation**: Each level of indentation is *4 spaces*.

  **Braces**: Braces always comes on the line following the statement.

    Example:
```c
void cool_function(void)
{
    int cool;
    for (cool = 0; cool < COOL_LIMIT; cool++)
    {
        [...]
        if (cool == AWESOME)
        {
            [...]
        }
    }
}
```

  **If-statements**: Always use curly braces.
  
  Example
  ```c
  if(condition)
  {                             /*always use curly braces even if the 'if' only has one statement
      DoJustThisOneThing();        
  }
  
  if(argv[i][2] == 'h' &&      /*split 'if' conditions to multiple lines if the conditions are long */
     argv[i][3] == 'e' &&      /*or if it makes things more readable. */
     argv[i][4] == 'l' && 
     argv[i][5] == 'p')
  {
        /*example taken from args parsing code*/
        /* code */
  }
  else if(condition)
  {
        /* code */
  }
  else
  {
      /* code */
  }
  ```
  
  **Switch-statements**: Always keep the break statement last in the case, after any code blocks.

  Example
```c
switch(state)
{
    case 1:
    {               /* even if the case only has one line, use curly braces (similar reasoning as with if's) */ 
        doA(1);
    } break;
                        /* separate cases with a line */
    case 2:             /* unless it falls into the next one */
    case 3:
    {
        DoThisFirst();
    }                   /* no break, this one also falls through */
    case 4:
    {                   /* notice that curly braces line up with 'case' on line above */
        int b = 2;
        doA(b);
    } break;        /* putting 'break' on this line saves some room and makes it look a little nicer */

    case 5:
    {
        /* more code */
    } break;

    default:        /* It is nice to always have a default case, even if it does nothing */
    {
        InvalidDefaultCase(); /* or whatever, it depends on what you are trying to do. */
    }
}
```


  **Line length**: There's no hard limit but if possible keep lines shorter than *80 characters*.
    
    
###### Vimrc 
 For those of you who use vim, add this to your vimrc to ensure proper indenting.
 ```vimrc
"####Indentation settings
:filetype plugin indent on
" show existing tab with 4 spaces width
:set tabstop=4
" when indenting with '>', use 4 spaces width
:set shiftwidth=4
" On pressing tab, insert 4 spaces
:set expandtab
" fix indentation problem with types above function name
:set cinoptions+=t0
" fix indentation of { after case
:set cinoptions+==0
" fix indentation of multiline if
:set cinoptions+=(0   "closing ) to let vimrc hylighting work after this line

"see http://vimdoc.sourceforge.net/htmldoc/indent.html#cinoptions-values
"for more indent options
 ```

###### Indent command (currently does not indent switch/cases properly)

```
indent [FILE] -npcs -i4 -bl -Tcst_wave -Tcst_wave_header -Tcst_rateconv \
      -Tcst_voice -Tcst_item -Tcst_features -Tcst_val -Tcst_va -Tcst_viterbi \
      -Tcst_utterance -Tcst_vit_cand_f_t -Tcst_vit_path_f_t -Tcst_vit_path \
      -Tcst_vit_point -Tcst_string -Tcst_lexicon -Tcst_relation \
      -Tcst_voice_struct -Tcst_track -Tcst_viterbi_struct -Tcst_vit_cand \
      -Tcst_tokenstream -Tcst_tokenstream_struct -Tcst_synth_module \
      -Tcst_sts_list -Tcst_lpcres -Tcst_ss -Tcst_regex -Tcst_regstate \
      -Twchar_t -Tcst_phoneset -Tcst_lts_rewrites -Tlexicon_struct \
      -Tcst_filemap -Tcst_lts_rules -Tcst_clunit_db -Tcst_cg_db \
      -Tcst_audio_streaming_info -Tcst_audio_streaming_info_struct -Tcst_cart \
      -Tcst_audiodev -TVocoderSetup -npsl -brs -bli0 -nut
```


