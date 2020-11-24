# RonaCop UV Steriliser: A SAFE Arduino controlled UV-C Steriliser for domestic use.

<!--- [![HitCount](http://hits.dwyl.com/tiaantiaan/RonaCopUVSterilizer.svg)](http://hits.dwyl.com/tiaantiaan/RonaCopUVSterilizer)  --->
[![License: MIT](https://img.shields.io/github/license/tiaantiaan/RonaCopUVSterilizer?style=for-the-badge)](https://opensource.org/licenses/MIT)

There are a few commercial and DIY UV sterilisers out there that aim to inactivate the SARS-CoV-2 virus on objects such as masks and everyday items. After reading up on a lot of scienticic research on the topic and investigating some existing solutions, I found that there are some really good systems as well as some really unsafe devices out there..

This project hopes to create a solution that addresses some of these safely concerns and add a few features to increase the safety and reliability of a UV-C steriliser for household items.

## WARNING: UV-C light is dangerous as it can modify DNA, cause burns and cause damage to the eyes. NEVER LOOK INTO A UV-C LIGHT WHEN IT IS ON and NEVER expose any part of your body to it.

## Safety considerations
### Use the correct type of UV light
Some sterilisers on the market use UVA and UVB light sources. Although effective at other forms of sterilisation, they will not deactivate the SARS-CoV-2 virus. Only UV-C and far-UV-C has been proven to work. UV-C radiation (wavelengths between 200 and 280 nm), is not present in normal sunlight experienced on earth (like UVA and UVB) as wavelengths lower than ~300 nm are absorbed by the ozone layer.

Exposure to UV-C light has been proven to kill virusses when applied in specific dosages. It has been found that energy dosages of between 7 J/m2 and 241 J/m2 kill different types of coronavisuees [1, 2] A, presently unreviewed, study by [3] suggests that a dosage of 41 J/m2 inactivates the SARS-CoV-2 virus. The energy that reaches the material from a UV-C lamp is determined by the radiation level of the lamp, the distance of the lamp to the object being sterilised as well as the exposure time. These factors have to be taken into account when designing a solution.

A good summary of the use of UV-C light in the current COVID-19 pandemic by the NIH can be found here: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC7435279/

### Exposure to UV-C light
**According to the NIH [4], UV-C light at 254 nm is harmful to the eyes and skin and, therefore, it is recommended to use it in setups that avoid direct human exposure**. The present solution aims to fully enclose the light in an enclosure and use a light sensor to see if the light works.

### Lamp lifetime
The radiation a lamp emits decreases as the lamp ages, thus requiring longer exposure times to obtain the same level of exposure. A lamp's datasheet usually provides a graph indicating how the radiation level decreases with hours of use.

### Lamp type
Look at the datasheet of the lamp to determine what frequencies it emits to make sure it is indeed UV-C. There has also been reports of fake UV-C lights being sold on some Chinese based websites. So make sure you use a lamp from a reputable brand.

### Lamp failure
Thinking the lamp is sterilising, while the lamp is off (due to failure) can cause a false sense of security.

### UV-C damages materials
Extended expose of certain materials (such as some plastics) to UV-C light can cause them to deteriorate and become brittle. This could reduce the effectiveness of some items like masks in filtering out harmful particles. The exposure time of the items thus have to be capped at a certain level to not cause material damage but still damage the virus effectively.

### Repositioning sterilised items
Only the areas of an object that are exposed to UV-C light are being sterilised. When sterilising a mask for example, some places may not receive direct exposure. It is therefore importand to reposition the item after a while to ensure that the entire surface gets UV-C exposure.

### Different exposure times
Porous surfaces, such as the material on masks, may need onger exposure times than hard surfaces to ensure that the desired UV-C dosage gets applied to the more obfuscated areas of the material.

### User errors
User testing has shown that users tend to put an item in the steriliser and forget about it. This may be an unsafe practice as firstly the material of the object may begin to deteriorate. Or a person may have intended to sterilise more objects or reposition them but forgot about it, resulting in them having to use partially or unsterilised objects.

# The solution
Taking the above safetly concern into account, this project incorporates the following:
- Fully enclosed light source to protect users from UV-C radiation.
- Safety switch that prevents the lamp from being on when the lid of the enclosure is opened.
- A light sensor to detect if the lamp is on and warn the user of lamp failure.
- A LED indicating if is the lamp is on.
- A timer that turns off the lamp after a preset time
- An exposure time selector to allow for the exposure time to be specified based on the material.
- An audible alarm that sounds when sterilization is done.
- A counter that keeps track of the time the light has been on to determine when the light needs replacing.
- A backlit LCD info display allowing operation in the dark.
- A plastic case that allows it to be easily washed and disinfected.
- A temperature sensor was added more out of interest to see how warm the incase of the case gets when the lamp is on.

## Parts
- Plastic enclosure
- Heavy duty aluminium foil
- Philips TUV 15W germicidal lamp
- Lamp ballast
- Lamp holders
- Plastic enclosure for the electronics
- Metal grid for the floor

### Electronics
- Arduino nano
- LCD screen with I2C backpack
- 2 push buttons
- 5V power supply
- 2 Microswitches
- 5V relay
- Light sensor

## Step 1: The enclosure
I used a non transparent plastic enclosure and lined with aluminium foil. Aluminium is an effective reflector of UV-C light. I found that a glue stick used for sticking paper worked nicely in adhering the foil to the plastic.

The 2 microswitches were located below each handle and secured with small nuts and bolts.


For the lamp, I used a pre-build fluorescent tube holder that included a ballast and lamp holders. I had to cut it a bit shorter so that it fit the 3ft fluorescent tube. I mounted this to the bottom of the case. And placed a removable grid on top of some long screws mounted above it.

My first prototype had the lamp mounted on the underside of the lid, but I found that items kept touching the lamp and the lamp could also get damaged when removing the lid and placing it on another surface.

I also mounted the light sensor so that it points directly at the lamp.

## Step 2: The electronics
The electronics were wired as follows:
![Schematic](schematic.png)


## Step 3: The code
Upload the file:'ronacop_uv_controller.ino' to your arduino using the Arduino IDE. 

## Step 4: Usage
Place an item to sterilise inside the box and close the lid.


Power the device on and you should see the following screen:


Select a time and the indicator light will light up and the timer will start counting down. After the timer ends, an audible alarm will sound and indicate the total hours that the lamp has been used.

If light does not detect that the lamp is on, a warning tone will sound and a message will appear:

This usually means that the lid is not properly closed of that there is something wrong with your lamp.


### Demo:









The lamp 

# Future improvements
- Use a case that allows one handed operation
- Allow the device to send notifications to a phone


## References
 
[1] M Weiss, M.C. Horzinek. "Resistance of Berne virus to physical and chemical treatment", *Veterinary Microbiology*, vol. 11, pp. 41-49, 1986.

[2] M.E.R Darnell, et al. "Inactivation of the coronavirus that induces severe acute respiratory syndrome, SARS-CoV", *Journal of Virological Methods*, vol. 121, pp. 85-94, 2004.

[3] H Inagaki H, et al. "Rapid inactivation of SARS-CoV-2 with Deep-UV LED irradiation.", Preprint doi: https://doi.org/10.1101/2020.06.06.138149. (unreviewed preprint), 2020.





