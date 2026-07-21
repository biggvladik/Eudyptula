# Eudyptula
My solutions to Eudyptula challenges

-------------------------------------
TASK 1
-------------------------------------

Write a Linux kernel module, and stand-alone Makefile, that when loaded
prints to the kernel debug log level, "Hello World!"  Be sure to make
the module be able to be unloaded as well.

The Makefile should build the kernel module against the source for the
currently running kernel, or, use an environment variable to specify
what kernel tree to build it against.

Please show proof of this module being built, and running, in your
kernel.  What this proof is is up to you, I'm sure you can come up with
something.  Also be sure to send the kernel module you wrote, along with
the Makefile you created to build the module.

-------------------------------------
TASK 2
-------------------------------------
Now that you have written your first kernel module, it's time to take
off the training wheels and move on to building a custom kernel.  No
more distro kernels for you, for this task you must run your own kernel.
And use git!  Exciting isn't it!  No, oh, ok...

The tasks for this round is:
  - download Linus's latest git tree from git.kernel.org (you have to
    figure out which one is his, it's not that hard, just remember what
    his last name is and you should be fine.)
  - build it, install it, and boot it.  You can use whatever kernel
    configuration options you wish to use, but you must enable
    CONFIG_LOCALVERSION_AUTO=y.
  - show proof of booting this kernel.  Bonus points for you if you do
    it on a "real" machine, and not a virtual machine (virtual machines
    are acceptable, but come on, real kernel developers don't mess
    around with virtual machines, they are too slow.  Oh yeah, we aren't
    real kernel developers just yet.  Well, I'm not anyway, I'm just a
    script...)  Again, proof of running this kernel is up to you, I'm
    sure you can do well.

Hint, you should look into the 'make localmodconfig' option, and base
your kernel configuration on a working distro kernel configuration.
Don't sit there and answer all 1625 different kernel configuration
options by hand, even I, a foolish script, know better than to do that!

After doing this, don't throw away that kernel and git tree and
configuration file.  You'll be using it for later tasks, a working
kernel configuration file is a precious thing, all kernel developers
have one they have grown and tended to over the years.  This is the
start of a long journey with yours, don't discard it like was a broken
umbrella, it deserves better than that.

-------------------------------------
TASK 3
-------------------------------------
Now that you have your custom kernel up and running, it's time to modify
it!

The tasks for this round is:
  - take the kernel git tree from Task 02 and modify the Makefile to
    and modify the EXTRAVERSION field.  Do this in a way that the
    running kernel (after modifying the Makefile, rebuilding, and
    rebooting) has the characters "-eudyptula" in the version string.
  - show proof of booting this kernel.  Extra cookies for you by
    providing creative examples, especially if done in intrepretive
    dance at your local pub.
  - Send a patch that shows the Makefile modified.  Do this in a manner
    that would be acceptable for merging in the kernel source tree.
    (Hint, read the file Documentation/SubmittingPatches and follow the
    steps there.)

-------------------------------------
TASK 4
-------------------------------------
Wonderful job in making it this far, I hope you have been having fun.
Oh, you're getting bored, just booting and installing kernels?  Well,
time for some pedantic things to make you feel that those kernel builds
are actually fun!

Part of the job of being a kernel developer is recognizing the proper
Linux kernel coding style.  The full description of this coding style
can be found in the kernel itself, in the Documentation/CodingStyle
file.  I'd recommend going and reading that right now, it's pretty
simple stuff, and something that you are going to need to know and
understand.  There is also a tool in the kernel source tree in the
scripts/ directory called checkpatch.pl that can be used to test for
adhering to the coding style rules, as kernel programmers are lazy and
prefer to let scripts do their work for them...

And why a coding standard at all?  That's because of your brain (yes,
yours, not mine, remember, I'm just some dumb shell scripts).  Once your
brain learns the patterns, the information contained really starts to
sink in better.  So it's important that everyone follow the same
standard so that the patterns become consistent.  In other words, you
want to make it really easy for other people to find the bugs in your
code, and not be confused and distracted by the fact that you happen to
prefer 5 spaces instead of tabs for indentation.  Of course you would
never prefer such a thing, I'd never accuse you of that, it was just an
example, please forgive my impertinence!

Anyway, the tasks for this round all deal with the Linux kernel coding
style.  Attached to this message are two kernel modules that do not
follow the proper Linux kernel coding style rules.  Please fix both of
them up, and send it back to me in such a way that does follow the
rules.

What, you recognize one of these modules?  Imagine that, perhaps I was
right to accuse you of the using a "wrong" coding style :)

Yes, the logic in the second module is crazy, and probably wrong, but
don't focus on that, just look at the patterns here, and fix up the
coding style, do not remove lines of code.

-------------------------------------
This is Task 05 of the Eudyptula Challenge
------------------------------------------
Yeah, you survived the coding style mess!  Now, on to some "real"
things, as I know you are getting bored by these so far.

So, simple task this time around:
  - take the kernel module you wrote for task 01, and modify it so that
    when a USB keyboard is plugged in, the module will be automatically
    loaded by the correct userspace hotplug tools (which are implemented
    by depmod / kmod / udev / mdev / systemd, depending on what distro
    you are using.)

Yes, so simple, and yet, it's a bit tricky.  As a hint, go read chapter
14 of the book, "Linux Device Drivers, 3rd edition."  Don't worry, it's
free, and online, no need to go buy anything.


