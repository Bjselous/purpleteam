#include <Arduino.h>

const char* htmlHomePage PROGMEM = R"HTMLHOMEPAGE(
<!DOCTYPE html>
<html>
  <head>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
    <style>
    .driveArrows {
      font-size:70px;
      color:red;
    }
    .turretArrows {
      font-size:70px;
      color:yellow;
    }
    .empty {
        display: inline-block;
        min-height : 80px;
        color:red;
    }
    .circularArrows {
      font-size:80px;
      color:yellow;
    }
    .waterSymbols {
      font-size:60px;
      color:blue;
    }
    .button {
      background-color:white;
      border-radius:25%;
      box-shadow: 5px 5px #888888;
    }
    td:active {
      transform: translate(5px,5px);
      box-shadow: none; 
    }

    .noselect {
      -webkit-touch-callout: none; /* iOS Safari */
        -webkit-user-select: none; /* Safari */
         -khtml-user-select: none; /* Konqueror HTML */
           -moz-user-select: none; /* Firefox */
            -ms-user-select: none; /* Internet Explorer/Edge */
                user-select: none; /* Non-prefixed version, currently
                                      supported by Chrome and Opera */
    }
    </style>

    <script>
        
        console.log("Loading script");
        console.log("");

        var webSocketUrl = "ws:\/\/" + window.location.hostname + "/ws";
        var websocket;
        
        function initWebSocket() 
        {
            console.log("Initialising websocket");
            console.log("");

            websocket = new WebSocket(webSocketUrl);
            websocket.onopen    = function(event){};
            websocket.onclose   = function(event){setTimeout(initWebSocket, 2000);};
            websocket.onmessage = function(event){};
        }

        function onTouchStartAndEnd(value) 
        {
            console.log("onTouchStartAndEnd-" + value);
            console.log("");
            websocket.send(value);
        }
            
    </script>

  </head>
  <body class="noselect" align="center" style="background-color:purple">
     
    <h1 style="color: black;text-align:center;">Purple Fire Fighter</h1>
    <h2 style="color: black;text-align:center;">Wi-Fi &#128658; Control</h2>
    
    <table id="mainTable" style="width:400px;margin:auto;table-layout:fixed" CELLSPACING=10>
        <tr>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("1")' ontouchstart='onTouchStartAndEnd("1")' onmouseup='onTouchStartAndEnd("3")' ontouchend='onTouchStartAndEnd("3")' class="button"><span class="driveArrows" >&#8679;</span></td>
            <td></td>
        </tr>
            
        <tr>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("2")' ontouchstart='onTouchStartAndEnd("2")' onmouseup='onTouchStartAndEnd("3")' ontouchend='onTouchStartAndEnd("3")' class="button"><span class="driveArrows" >&#8681;</span></td>
            <td></td>
        </tr>
    
        <tr>
            <td><span class="empty" ></span></td>
            <td><span class="empty" ></span></td>    
            <td><span class="empty" ></span></td>
        </tr>

        <tr>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("4")' ontouchstart='onTouchStartAndEnd("4")' onmouseup='onTouchStartAndEnd("6")' ontouchend='onTouchStartAndEnd("6")' class="button"><span class="turretArrows" >&#8679;</span></td>
            <td></td>
        </tr>

        <tr>
            <td onmousedown='onTouchStartAndEnd("7")' ontouchstart='onTouchStartAndEnd("7")' onmouseup='onTouchStartAndEnd("9")' ontouchend='onTouchStartAndEnd("9")' class="button"><span class="circularArrows" >&#8634;</span></td>
            <td onmousedown='onTouchStartAndEnd("10")' ontouchstart='onTouchStartAndEnd("10")' onmouseup='onTouchStartAndEnd("11")' ontouchend='onTouchStartAndEnd("11")' class="button"><span class="waterSymbols" >&#128167;</span></td>
            <td onmousedown='onTouchStartAndEnd("8")' ontouchstart='onTouchStartAndEnd("8")' onmouseup='onTouchStartAndEnd("9")' ontouchend='onTouchStartAndEnd("9")' class="button"><span class="circularArrows" >&#8635;</span></td>
        </tr>

        <tr>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("5")' ontouchstart='onTouchStartAndEnd("5")' onmouseup='onTouchStartAndEnd("6")' ontouchend='onTouchStartAndEnd("6")' class="button"><span class="turretArrows" >&#8681;</span></td>
            <td></td>
        </tr>

        <tr>
            <td onmousedown='onTouchStartAndEnd("10")' ontouchstart='onTouchStartAndEnd("10")' class="button"><span class="waterSymbols" >ON</span></td>
            <td onmousedown='onTouchStartAndEnd("0")' ontouchstart='onTouchStartAndEnd("0")' class="button"><span style="font-size:70px; color:red;">&#9888;</span></td>
            <td onmousedown='onTouchStartAndEnd("11")' ontouchstart='onTouchStartAndEnd("11")' class="button"><span class="waterSymbols" >OFF</span></td>
        </tr>

    </table>

    <script>

        console.log("disable default event listener");
        console.log("");

        document.getElementById("mainTable").addEventListener("touchend", function(event){
                event.preventDefault()
            });

        initWebSocket();  
        
       
        console.log("Ready");
        console.log("");     
    </script>
    
  </body>
</html> 

)HTMLHOMEPAGE";