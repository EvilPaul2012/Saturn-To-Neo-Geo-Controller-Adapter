# Saturn-To-Neo-Geo-Controller-Adapter
This is for an adapter that will convert a Sega Saturn controller to work on a Neo Geo.

Code is still in a testing get up and working so phase so it isn't as clean as Id like. 

###### Current features include 
- Actually working, sending Saturn data to the Neo Geo
- Button remapping

###### Future plans
- Rapid fire, current started.
- Change from digitalWrite to the bitwise way, I forget the name.
- Saving config

###### The stock button config is:
- A = A
- X = B
- Y = C
- Z = D
- Start = Start
- L = Coin

To start the button remapping best A + C + Start buttons. The light will turn on. After this press the buttons in the order you wish to set, the light will flash, and then you can continue to the next. The mapping order is A,B,C,D,Start,Coin,K2,K3. After all buttons have been set, the light will turn off.
