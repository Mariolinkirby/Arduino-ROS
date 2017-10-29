#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

/////////////////////create a node handler to do all of the hard node stuff for you///////////////
//thank you libraries
//this is used in all examples
ros::NodeHandle nh;

//////////////////////////////////////generic publisher////////////////////////////////////////////
//create a message (of type String) to send to listening node
std_msgs::String str_msg;
//create a publishing node to send data
//send (to everyone listerning) using channel "chatter"
//send data of (refrence to string that you want to send)
ros::Publisher chatter("chatter", &str_msg); 
//create a string with data
char hello[13] = "ACKNOWLEDGE";

//generic publisher
void RosPublisherAndVanillaArduino()
{
  str_msg.data = hello;         //fill message to send
  chatter.publish(&str_msg);    //publish message to channel "chatter"
  nh.spinOnce();                //spin node handler
  delay(1000);                  //wait so that all ros terminals can catch up
}

////////////////////////////////////////////generic subscriber/////////////////////////////////////
//generic subscriber
void messageCb(const std_msgs::Empty& toggle_msg) //always takes const ref to message as parameter
{
  digitalWrite(13, HIGH);         //blink the on board LED whenever we get a message
  delay(500);                     //turn on led for .5 seconds
  digitalWrite(13, LOW);          //ros will hold published message for 3 seconds...
  RosPublisherAndVanillaArduino();
}
//initiate a subscriber named "toggle_led"
//arguments are topic it listens to and calback function it uses
ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb);
void genericSubscriber()
{
  nh.spinOnce();                                  //have node handler run
  delay(1);                                       //wait 1ms so you listen as often as possible
}


void sub_with_ack()
{
  nh.spinOnce();
  delay(1);
}

///////////////////////////////////////////setup////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);          //set onboard led to output
  digitalWrite(13, LOW);        //turn off on board LED
  nh.initNode();                //initiate node
  nh.advertise(chatter);        //tell node to send data on "chatter"
  nh.subscribe(sub);            //tell node to listen for data on "sub"
}

///////////////////////////////////////////loop/////////////////////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  //RosPublisherAndVanillaArduino();
  //genericSubscriber();
  sub_with_ack();
}
