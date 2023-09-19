
#include <Arduino.h>

const char* htmlHomePage PROGMEM = R"HTMLHOMEPAGE(
<!DOCTYPE html>
<html>
  <head>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
    <style>
    .driveArrows {
      font-size:2em;
      color:black;
    }
    .turretArrows {
      font-size:2em;
      color:black;
    }
    .empty {
        display: inline-block;
        min-height : 2em;
        color:red;
    }
    .circularArrows {
      font-size:2em;
      font-weight:bold;
      color:black;
    }
    .waterSymbols {
      font-size:2em;
      color:black;
    }
    .button {
      border: solid;
      border-radius:25%;
      border-color:dark-purple;
      border-width: 2px;
    }
    td:active {
      transform: translate(5px,5px);
      box-shadow: none; 
      border-color:black;
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
         
    <table id="mainTable" style="width:400px;margin:auto;table-layout:fixed" CELLSPACING=10>
        <tr>
            <td></td>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("1")' ontouchstart='onTouchStartAndEnd("1")' onmouseup='onTouchStartAndEnd("3")' ontouchend='onTouchStartAndEnd("3")' class="button"><span class="driveArrows" >&#8679;</span></td>
            <td></td>
            <td></td>
        </tr>
            
        <tr>
            <td></td>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("2")' ontouchstart='onTouchStartAndEnd("2")' onmouseup='onTouchStartAndEnd("3")' ontouchend='onTouchStartAndEnd("3")' class="button"><span class="driveArrows" >&#8681;</span></td>
            <td></td>
            <td></td>
        </tr>
    
        <tr>
            <td><span class="empty" ></span></td>
            <td><span class="empty" ></span></td>    
            <td><span class="empty" ></span></td>
            <td><span class="empty" ></span></td>    
            <td><span class="empty" ></span></td>
        </tr>

        <tr>
            <td></td>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("4")' ontouchstart='onTouchStartAndEnd("5")' onmouseup='onTouchStartAndEnd("6")' ontouchend='onTouchStartAndEnd("6")' class="button"><span class="turretArrows" >&#8679;</span></td>
            <td></td>
            <td></td>
        </tr>

         <tr>
            <td></td>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("4")' ontouchstart='onTouchStartAndEnd("5")' onmouseup='onTouchStartAndEnd("6")' ontouchend='onTouchStartAndEnd("6")' class="button"><span class="turretArrows" >&#8679;</span></td>
            <td></td>
            <td></td>
        </tr>

        <tr>
            <td onmousedown='onTouchStartAndEnd("7")' ontouchstart='onTouchStartAndEnd("7")' onmouseup='onTouchStartAndEnd("9")' ontouchend='onTouchStartAndEnd("9")' class="button"><span class="circularArrows" >&#8634;</span></td>
            <td onmousedown='onTouchStartAndEnd("7")' ontouchstart='onTouchStartAndEnd("7")' onmouseup='onTouchStartAndEnd("9")' ontouchend='onTouchStartAndEnd("9")' class="button"><span class="circularArrows" >&#8634;</span></td>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("8")' ontouchstart='onTouchStartAndEnd("8")' onmouseup='onTouchStartAndEnd("9")' ontouchend='onTouchStartAndEnd("9")' class="button"><span class="circularArrows" >&#8635;</span></td>
            <td onmousedown='onTouchStartAndEnd("8")' ontouchstart='onTouchStartAndEnd("8")' onmouseup='onTouchStartAndEnd("9")' ontouchend='onTouchStartAndEnd("9")' class="button"><span class="circularArrows" >&#8635;</span></td>
        </tr>

        <tr>
            <td></td>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("5")' ontouchstart='onTouchStartAndEnd("4")' onmouseup='onTouchStartAndEnd("6")' ontouchend='onTouchStartAndEnd("6")' class="button"><span class="turretArrows" >&#8681;</span></td>
            <td></td>
            <td></td>
        </tr>
        
        <tr>
            <td></td>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("5")' ontouchstart='onTouchStartAndEnd("4")' onmouseup='onTouchStartAndEnd("6")' ontouchend='onTouchStartAndEnd("6")' class="button"><span class="turretArrows" >&#8681;</span></td>
            <td></td>
            <td></td>
        </tr>

        <tr>
            <td><span class="empty" ></span></td>
            <td><span class="empty" ></span></td>    
            <td><span class="empty" ></span></td>
            <td><span class="empty" ></span></td>    
            <td><span class="empty" ></span></td>
        </tr>

        <tr>
            <td></td>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("12")' ontouchstart='onTouchStartAndEnd("12")' onmouseup='onTouchStartAndEnd("14")' ontouchend='onTouchStartAndEnd("14")' class="button"><span class="driveArrows" >&#8679;</span></td>
            <td></td>
            <td></td>
        </tr>
            
        <tr>
            <td></td>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("13")' ontouchstart='onTouchStartAndEnd("13")' onmouseup='onTouchStartAndEnd("14")' ontouchend='onTouchStartAndEnd("14")' class="button"><span class="driveArrows" >&#8681;</span></td>
            <td></td>
            <td></td>
        </tr>

        <tr>
            <td><span class="empty" ></span></td>
            <td><span class="empty" ></span></td>    
            <td><span class="empty" ></span></td>
            <td><span class="empty" ></span></td>    
            <td><span class="empty" ></span></td>
        </tr>

        <tr>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("10")' ontouchstart='onTouchStartAndEnd("10")' class="button"><span class="waterSymbols" >ON</span></td>
            <td onmousedown='onTouchStartAndEnd("10")' ontouchstart='onTouchStartAndEnd("10")' onmouseup='onTouchStartAndEnd("11")' ontouchend='onTouchStartAndEnd("11")' class="button"><span class="waterSymbols" >&#128167;</span></td>
            <td onmousedown='onTouchStartAndEnd("11")' ontouchstart='onTouchStartAndEnd("11")' class="button"><span class="waterSymbols" >OFF</span></td>
            <td></td>
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