# AP-Final-Project-Phase2
The second phase of the final project

to execute, run "./utrip.out hotels.csv ratings.csv"

You can also use the following commands in this phase:
POST default_price_filter ? active true|false
* to activate/deactivate the default price filter which suggests the hotels that the user will most likely select (that is implemented by using statistics and certain conditions)

POST sort ? property <property> order ascending|descending
* to sort the hotels using property (i.e. id/name/star_rating/city/standard_room_price/deluxe_room_price/luxury_room_price/premium_room_price/average_room_price/rating_personal)
  
GET ratings ? hotel <hotel_id>
* to get the new ratings of a hotel (provided in a csv file)

POST manual_weights ? active true location <location> cleanliness <cleanliness> staff <staff> facilities <facilities> value_for_money <value_for_money>
* to set manual weights for different parameters of a hotel (which we'll use later to sort the hotels)
  
POST manual_weights ? active false
* to turn of manual weights
  
GET manual_weights
* to get the manual weights you've set before

NOTE that if manual weights are activated you can use "rating_personal" in the sort command to sort hotels by their weighted average

GET estimated_weights
* to get the estimated weights which are calculated using the ratings the user has given to different hotels (there's somewhat of an enhanced logic behind this which is not explained in this file, however the implementation is visible in the "User.cpp" file

NOTE that if manual_weights are not active, the program will estimate the weights (as mentioned above) and you can sort the hotels by using "rating_personal" in the sort command
