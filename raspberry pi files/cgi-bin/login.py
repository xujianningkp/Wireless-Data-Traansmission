#!/usr/bin/env python

import time
import cgi
import cgitb

cgitb.enable()

print "Content-type: text/html\n\n"

form=cgi.FieldStorage()

username=form["user_name"].value
password=form["password"].value

if username=="pi"and password=="mypass":
	#page_str="""
	#<h1>Login successful</h1><br>
	#<p>This page will be redirected in few seconds.</p>
	#<a href="http://99.168.99.25/login.html">Go Back to Login Page</a>
	#<script language="javascript">window.open('http://99.168.99.25:8081',"self")</script>
	#"""
	
	#<h1>Webcam Live Streaming</h1>
	#<img src="http://173.71.20.77:8081">
	#<p></p><br>
	#<input type="button" style="width:200px; height:40px" value="Download RPi Tutorial" onclick="window.open('https://app.box.com/s/zn5xjuukpsjhc2kh5mjo','_blank','resizable=yes')" />
	#<a href="http://173.71.20.77/login.html">Go Back Login Page</a>
	
	page_str="""
	<!DOCTYPE html>
	<html>


	<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=Edge"/>
	<link rel="shortcut icon" type="image/ico" href="http://173.71.20.77/images/favicon.ico"/>
	<link href="http://173.71.20.77/styles.css" rel="stylesheet" type="text/css" media="screen">
	<title>UNT | Weather Station</title>

	<!--The following script tag downloads a font from the Adobe Edge Web Fonts server for use within the web page. We recommend that you do not modify it.-->
	<script>var __adobewebfontsappname__="dreamweaver"</script>
	<script src="http://use.edgefonts.net/acme:n4:default;lilita-one:n4:default;yeseva-one:n4:default;droid-sans-mono:n4:default;amaranth:n4:default;merienda-one:n4:default;sail:n4:default;luckiest-guy:n4:default;fugaz-one:n4:default;poller-one:n4:default.js" type="text/javascript"></script>
	<style>
	body {
	background-image:url(http://173.71.20.77/images/background.png);
	background-repeat:repeat-x;
	}
	</style>
	</head>


	<body>
	<div id="container">
	
    	<div id="header">
    	<a class="logo1">WEATHER</a><br>
        <a class="logo2">UNIVERSITY OF NORTH TEXAS</a>
        <hr class="style1"></hr>
        <hr class="style2"></hr>
        <div class="nav">
        	<ul>
            <li><a href="http://173.71.20.77/index.html">HOME</a></li>
            <li><a href="http://173.71.20.77/projects.html">PROJECTS</a></li>
            <li><a href="http://173.71.20.77/contact.html">CONTACT</a></li>
            <li><a href="http://173.71.20.77/login.html">LOGIN</a></li>
            </ul>
        
        </div>
        
    	<div id="blank"></div>
    
    
    	<div id="blank1"></div>

    	<div id="subheader">
    	<a class="subtitle1">Data Files Storage</a>
        </div>
    
    	<div id="blank1"></div>
    
    	<div id="content">
    	<div>
        <a class="subtitle2">Data Logger File (CSV):</a>
        <p>Date/Time/Built-In Temp(F)/Outside Temp(F)/Moisture(%)</p><br>
        <p><b>(NHC Live Streaming)<b></p>
        <img src="http://173.71.20.77:8081" width="426" height="340">
        </div>
        
        <div>      
        <input type="button" style="width:200px; height:40px" value="Download" onclick="window.open('http://173.71.20.77/dataLog.csv','resizable=yes')" />


        </div>
        </div>
        
    
    	<div id="footer">
    	<p class="foottext">Copyright &copy; 2014 | All Rights Reserved | 
        <a href="http://173.71.20.77/index.html">UNT Weather</a> |
        <a href="https://engineering.unt.edu/electrical/home">Department of Electrical Engineering</a></p>
        
        <div class="nav2">
        	<ul>
            <li><a href="http://www.unt.edu" target="_blank"</a><img src="http://173.71.20.77/images/unt.png" width="50" height="50" ></li>
            <li><a href="http://www.raspberrypi.org" target="_blank"</a><img src="http://173.71.20.77/images/raspberry-pi.png" width="50" height="50"></li>
            <li><a href="http://www.arduino.cc" target="_blank"</a><img src="http://173.71.20.77/images/arduino.png" width="50" height="50"></li>
            </ul>
        </div>
        </div>
    
	</body>


	</html>
	"""
	print page_str

else:
	page_str="""
	<h1>Unable to Log On!</h1><br>
	<p>User ID and/or password that doesn't match our records. Please try again.</p>
	<p></p><br>
	<a href="http://173.71.20.77/login.html">Go Back Login Page</a>
	"""
	print page_str

#if "user_name" not in form:
#    print "<h1>No username was entered</h1>"
#else:
#    text=form["user_name"].value	
#    if text=="etkait":
#	print "<h1>Hello kit asshole!</h1>"
#    else:
#    	print "<h1>Username:</h1>"
#    	print cgi.escape(text)
#if "password" not in form:
#    print "<h1>No password was entered</h1>"
#else:
#    text=form["password"].value
#    print "<h1>Password:</h1>"
#    print cgi.escape(text)

