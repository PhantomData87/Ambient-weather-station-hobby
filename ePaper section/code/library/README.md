# What this is?
This is my finished library & thing to test the 1.54inch ePaper display screen  
Here is link to the original screen; https://www.waveshare.com/1.54inch-e-Paper-Module.htm  
  
Now the reason why this exist instead of using the manufacturers code is simply this; It annoyed me greatly how messy it was. Than when I started to peer into the inner workings to understand my screen on why it was failing. I was annoyed further from how inefficient it was.  
  
Now it's not my claim that this code is somehow "superior" but rather a bit more "managable". You be the judge of that.  
  
# Progress
1. Done making "testing" class  
2. Done writing main library  
  - You can do MOST of the funcitons of the original manufacturer's code  (Missing; Draw arbitrary line)  
  - Introduced more precise pixel precision  
  - Introduced better rotation  
  - Introduced array-less drawing (Explained below)  
  - Simplified class structure (no longer 3 files, now just one massive file)  
  - Heavy reduce usage on ram  
3. Need to figure out if one can read screen (To preserve things that had been drawn)  
4. Need to optimize further the code  
5. Need to innovate further the code  

# Explanation of why I decided to go for "array-less"
I had bought a simple chip named "Adafruit ItsyBitsy 32u4 - 5V 16MHz", and I didn't realize early on the important need of having a large storage & ram space. I lucked out on the storage, but the ram on this is **2K bytes**. Thus when I ran the original code I had around 3/4th of the memory dedicated to an array. Which I later found out it was really unncessary since all it did was store info before sneding it anyways. So as a challenge I wanted to see if I could recreate the code without the reliance on an array. Answer is YES!  

Currently this exists to permit mroe lower end or memory limited devices to work more properely without the need to sacrifice a huge portion of memory.
