# hovergames3

## Overview

Our team is very excited by this Hackster.io NXP Hovergames competition because optimizing food production positively impacts everyone.
By utilizing RGB-D camera data (NVDI, growth, pests, etc.), a JXCT 7-in-one soil sensor (NPK, pH, salinity, moisture, and temperature), GPS data (location and elevation), and Bosch BME688 sensor data (greenhouse gases, moisture, temperature) we measure NDVI plant health, soil health, and greenhouse gas improvements. This allows us to provide actionable recommendations for water, fertilization, and the best areas to plant/not plant.
The Normalized Difference Vegetation Index (NVDI)  is a standard used with satellite imagery to identify vegetation health. NVDI (calculated as NDVI = (NIR - RED) / (NIR + RED)) yields a number between -1 and 1: -1..0 = dead or no plants, 0.0.33 = unhealthy plants, 0.33..0.66 = moderately healthy plants, and 0.66..1 = healthy plants. While this gives you an overall indicator of plant health, it doesn’t explain the problem or the action farmers should take to correct it. In addition, existing systems that collect this data are typically only updated once a week via satellite data. We can collect this data with drones daily to track crops more effectively. Our down-looking sensor (the Oak-D depth camera) can capture plant growth rates.
We can then direct the quadcopter to collect more information about underperforming areas. The standard for testing soil health looks at pH (6.5 is optimal for growth), nutrients (NPK = Nitrogen, Phosphorous, and Potassium), salinity (via electric conductivity), moisture, and temperature. To collect this data, the quadcopter will land in suspect areas inserting a five-pin probe into the ground to take a sample. We can also take close-up pictures of the crops to identify possible pests or diseases. We can provide detailed crop health data and actions to improve yields.
The 97% of greenhouse gases that cause global warming include carbon dioxide (CO2 79%), Methane (CH4 11%), and Nitrous Oxide (NO2 7%). The BME688 can detect all of these compounds in the air or on landing. By making crops healthier, we allow them to remove more C02 from the air and convert it into O2. By targeting fertilizers, we can reduce NO2 and CH4. In addition, the Bosch sensor will allow us to collect temperature, moisture, and pressure. We can use this data to show reductions in greenhouse gases. We intend to look for correlations between soil temperature and moisture by looking at the air readings at a specific height above the ground.
What we were able to achieve:
Drone flight
Collecting BME688 data.
Collecting sample soil using a 7in1 sensor.
Collecting OAK-D imagery data.
Calculates NVDI data using Open Drone Map.

## Install

1. NAVQ+ - follow directions in [navq_plus](navq_plus)
2. FMUK66v3 - follow directions in [fmuk66v3](fmuk66v3)
3. TFMini - follow directions in [tfmini](tfmini)
4. Soil - follow directions in [soil](soil)
5. BME688 - follow directions in [bme688](bme688)
6. OAKD - follow directions in [oakd](oakd)
7. ODM - follow directions in [odm](odm)
