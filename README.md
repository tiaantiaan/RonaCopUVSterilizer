# A safe arduino controlled UV-C Steriliser that actually works (based on sound science)

There are a few commercial and DIY UV sterilisers out there that aim to inactivate the SARS-CoV-2 virus on objects such as masks and everyday items. After reading up on a lot of scienticic research on the topic and investigating some existing solutions, I found that there are some really good systems as well as some really unsafe devices out there that people use to sterilise items.

This project hopes to create a solution that addresses some of these safely concerns and add a few features to increase the safety and reliability of a UV-C steriliser for household items.

## Safety 
## WARNING: UV-C light is dangerous as it can modify DNA, cause burns and cause damage to the eyes. NEVER LOOK INTO A UV-C LIGHT WHEN IT IS ON and NEVER expose any part of your body to it.

### Safety considerations
## Use the correct type of UV light
Some sterilisers on the marketuse UVA and UVB light sources. Although effective at other forms of sterilisation, they will not deactivate the SARS-CoV-2 virus. Only UV-C and far-UV-C has been proven to work.

UV-C radiation (wavelengths between 200 and 280 nm), is not present in normal sunlight experienced on earth (like UVA and UVB) as wavelengths lower than ~300 nm are absorbed by the ozone layer.

Exposure to UV-C light has been proven to kill virusses when applied in specific dosages. It has been found that energy dosages of between 7 J/m2 and 241 J/m2 kill different types of coronavisuees [1, 2] A, presently unreviewed, study by [3] suggests that a dosage of 41 J/m2 inactivates the SARS-CoV-2 virus. The energy that reaces the material from a UV-C lamp is determined by the radiation level of the lamp, the distance of the lamp to the object being sterilised as well as the exposure time.

## Exposure to UV-C light
According to the NIH [4], UV-C light at 254 nm is harmful to the eyes and skin and, therefore, it is recommended to use it in setups that avoid direct human exposure. The present solution aims to fully enclose the light in an enclosure and use a light sensor to see if the light works.

## Lamp lifetime
The radiation a lamp emits decreases as the lamp ages, thus requiring longer exposure times to obtain the same level of exposure. A lamps data sheet usually provides a graph indicating how the radiation level decreases with wours of use.

## Lamp failure
Thinking the lamp is seterilising, while the lamp is off (due to failure) can cause a false sense of security.

## Lamp type
Look at the datasheet of the lamp to determine what frequencies it emits to make sure it is indeed UV-C. There has also been reports of fake UV-C lights being sold on some Chinese based websites. So make sure you use a lamp from a reputable brand.

## Repositioning sterilised items
Only the areas of an object that are exposed to UV-C light are being sterilised. When sterilising a mask for example, some places may not receive direct exposure. It is therefore importand to reposition the iitem after a while to ensure that the entire item gets UV-C exposure.

## User forgetting to reposition or put in the next item
User testing has shown that users tend to put in an item in the steriliser and forget about it. This may be an unsafe practice as firstly the material of the object may begin to deteriorate (e.g. masks will become less effective). Or a person may have intended to sterilise more objects or reposition them

## UV-C damages materials

### Some existing UV sterilisers are unsafe because they do not actually deactivate the SARS-Cov-2 virus.
There are some devices on the market that are labeled "UV sterilisers" and people assume that they will be able to kill the SARS-Cov-2. Devices fitted with UV-A or UV-B lights may be effective at other types of sterilisation, but do very little to the SARS-Cov-2 virus. o 


This project aims to address some of these unsafe practices by using

I did a lot of reading up on the efficacy of using UV light do deactivate There are some really good systems, but unfortunately there are also some really unsafe devices

A component of the RonaCop project: A UVC sterilizer box used for sterilizing masks and everyday objects.

This is part of the RonaCop project that aims to reduce the spread of the Corona virus within households by using technology.



## The science behind UV sterilisation




A good summary of the use of UV-C light in the current COVID-19 pandemic by the NIH can be found here: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC7435279/



# The Idea

# The issues
- Lamp life
- Safety
- Exposure coverage (turn over)
- Effective exposure time
- Reminderthat its done.

# The solution
- Arduino with screen and safety 




## References
 
[1] M Weiss, M.C. Horzinek. "Resistance of Berne virus to physical and chemical treatment", *Veterinary Microbiology*, vol. 11, pp. 41-49, 1986.
[2] M.E.R Darnell, et al. "Inactivation of the coronavirus that induces severe acute respiratory syndrome, SARS-CoV", *Journal of Virological Methods*, vol. 121, pp. 85-94, 2004.
[3] H Inagaki H, et al. "Rapid inactivation of SARS-CoV-2 with Deep-UV LED irradiation.", Preprint doi: https://doi.org/10.1101/2020.06.06.138149. (unreviewed preprint), 2020.





