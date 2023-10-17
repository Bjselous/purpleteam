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
    .heading {
      font-size:2em;
      color:black;
    }
    .empty {
        display: inline-block;
        min-height : 2em;
        color:red;
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
      width: 50px;
    }
    td
    {
      min-width:50px;
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
         
    <table id="driveTable" style="min-width:400px; margin:10px auto;table-layout:fixed; border: 1px solid black; border-radius: 10px;" CELLSPACING=10>

        <tr>
            <td></td>
            <td colspan="3"><span class="heading">Drive<span></td>
            <td></td>
        </tr>

        <tr>
            <td></td>
            <td></td>
            <!-- Creep Forward -->
            <td onmousedown='onTouchStartAndEnd("15")' ontouchstart='onTouchStartAndEnd("15")' onmouseup='onTouchStartAndEnd("3")' ontouchend='onTouchStartAndEnd("3")' class="button"><span class="driveArrows" >&#8593;</span></td>
            <td></td>
            <td></td>
        </tr>

        <tr>
            <td></td>
            <td></td>
            <!-- Forward -->
            <td onmousedown='onTouchStartAndEnd("1")' ontouchstart='onTouchStartAndEnd("1")' onmouseup='onTouchStartAndEnd("3")' ontouchend='onTouchStartAndEnd("3")' class="button"><span class="driveArrows" >&#8648;</span></td>
            <td></td>
            <td></td>
        </tr>
            
        <tr>
            <td></td>
            <td></td>
            <!-- Backwards -->
            <td onmousedown='onTouchStartAndEnd("2")' ontouchstart='onTouchStartAndEnd("2")' onmouseup='onTouchStartAndEnd("3")' ontouchend='onTouchStartAndEnd("3")' class="button"><span class="driveArrows" >&#8650;</span></td>
            <td></td>
            <td></td>
        </tr>

        <tr>
            <td></td>
            <td></td>
            <!-- Creep Backwards -->
            <td onmousedown='onTouchStartAndEnd("16")' ontouchstart='onTouchStartAndEnd("16")' onmouseup='onTouchStartAndEnd("3")' ontouchend='onTouchStartAndEnd("3")' class="button"><span class="driveArrows" >&#8595;</span></td>
            <td></td>
            <td></td>
        </tr>
      
    </table>
    
    <table id="turretTable" style="min-width:400px; margin:auto;table-layout:fixed; border: 1px solid black; border-radius: 10px;" CELLSPACING=2>

        <tr>
            <td></td>
            <td></td>
            <td colspan="3"><span class="heading">Turret</span></td>
            <td></td>
            <td></td>
        </tr>

        <tr>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("21")' ontouchstart='onTouchStartAndEnd("21")' class="button"><span class="turretArrows" >ON</span></td>
            <td></td>
            <!--Elevate Turret 1-->
            <td onmousedown='onTouchStartAndEnd("18")' ontouchstart='onTouchStartAndEnd("18")' class="button"><span class="turretArrows" >1</span></td>
            <td></td>
            <td onmousedown='onTouchStartAndEnd("22")' ontouchstart='onTouchStartAndEnd("22")' class="button"><span class="turretArrows" >OFF</span></td>
            <td></td>
        </tr>

        <tr>
            <td></td>
            <td></td>
            <td></td>
            <!--Elevate Turret 5-->
            <td onmousedown='onTouchStartAndEnd("17")' ontouchstart='onTouchStartAndEnd("17")' class="button"><span class="turretArrows" >5</span></td>
            <td></td>
            <td></td>
            <td></td>
        </tr>

         <tr>
            <td></td>
            <td></td>
            <td></td>
            <!--Elevate Turret 10-->
            <td onmousedown='onTouchStartAndEnd("4")' ontouchstart='onTouchStartAndEnd("4")' class="button"><span class="turretArrows" >10</span></td>
            <td></td>
            <td></td>
            <td></td>
        </tr>

        <tr>
            <td onmousedown='onTouchStartAndEnd("20")' ontouchstart='onTouchStartAndEnd("20")' class="button"><span class="turretArrows" >1</span></td>
            <!-- TRAVERSE TURRET ANTICLOCKWISE -->
            <td onmousedown='onTouchStartAndEnd("19")' ontouchstart='onTouchStartAndEnd("19")' class="button"><span class="turretArrows" >5</span></td>
            <!-- TRAVERSE TURRET ANTICLOCKWISE -->
            <td onmousedown='onTouchStartAndEnd("8")' ontouchstart='onTouchStartAndEnd("8")' class="button"><span class="turretArrows" >10</span></td>
            <td></td>
            <!-- TRAVERSE TURRET CLOCKWISE -->
            <td onmousedown='onTouchStartAndEnd("7")' ontouchstart='onTouchStartAndEnd("7")' class="button"><span class="turretArrows" >10</span></td>
            <!-- SLOW TRAVERSE TURRET CLOCKWISE -->
            <td onmousedown='onTouchStartAndEnd("28")' ontouchstart='onTouchStartAndEnd("28")' class="button"><span class="turretArrows" >5</span></td>

            <td onmousedown='onTouchStartAndEnd("29")' ontouchstart='onTouchStartAndEnd("29")' class="button"><span class="turretArrows" >1</span></td>
        </tr>

        <tr>
            <td></td>
            <td></td>
            <td></td>
            <!-- Depress Turret 10-->
            <td onmousedown='onTouchStartAndEnd("27")' ontouchstart='onTouchStartAndEnd("27")' class="button"><span class="turretArrows" >10</span></td>
            <td></td>
            <td></td>
            <td></td>
        </tr>
        
        <tr>
            <td></td>
            <td></td>
            <td></td>
            <!-- Depress Turret 5-->
            <td onmousedown='onTouchStartAndEnd("26")' ontouchstart='onTouchStartAndEnd("26")' class="button"><span class="turretArrows" >5</span></td>
            <td></td>
            <td></td>
            <td></td>
        </tr>

        <tr>
            <td></td>
            <td></td>
            <td></td>
            <!-- Depress Turret 1-->
            <td onmousedown='onTouchStartAndEnd("5")' ontouchstart='onTouchStartAndEnd("5")' class="button"><span class="turretArrows" >1</span></td>
            <td></td>
            <td></td>
            <td></td>
        </tr>
      
    </table>

    <table id="actuatorTable" style="min-width:400px; margin:10px auto;table-layout:fixed; border: 1px solid black; border-radius: 10px;" CELLSPACING=10>

        <tr>
            <td></td>
            <td></td>
            <td><span class="heading">Actuator</span></td>
            <td></td>
            <td></td>
        </tr>

        <tr>
            <td></td>
            <td></td>
            <!-- Linear Actuator Up -->
            <td onmousedown='onTouchStartAndEnd("12")' ontouchstart='onTouchStartAndEnd("12")' onmouseup='onTouchStartAndEnd("14")' ontouchend='onTouchStartAndEnd("14")' class="button"><span class="driveArrows" >&#8679;</span></td>
            <td></td>
            <td></td>
        </tr>
            
        <tr>
            <td></td>
            <td></td>
             <!-- Linear Actuator Down -->
            <td onmousedown='onTouchStartAndEnd("13")' ontouchstart='onTouchStartAndEnd("13")' onmouseup='onTouchStartAndEnd("14")' ontouchend='onTouchStartAndEnd("14")' class="button"><span class="driveArrows" >&#8681;</span></td>
            <td></td>
            <td></td>
        </tr>

       </table>

    <table id="pumpTable" style="min-width:400px; margin:10px auto;table-layout:fixed; border: 1px solid black; border-radius: 10px;" CELLSPACING=10>

        <tr>
            <td></td>
            <td colspan="3"><span class="heading">Pump</span></td>
            <td></td>
        </tr>

        <tr>
            <td><span class="empty"></span></td>
            <td onmousedown='onTouchStartAndEnd("23")' ontouchstart='onTouchStartAndEnd("23")' class="button"><span class="waterSymbols" >1</span></td>  
            <td onmousedown='onTouchStartAndEnd("24")' ontouchstart='onTouchStartAndEnd("24")' class="button"><span class="waterSymbols" >2</span></td>
            <td onmousedown='onTouchStartAndEnd("25")' ontouchstart='onTouchStartAndEnd("25")' class="button"><span class="waterSymbols" >3</span></td>  
            <td><span class="empty"></span></td>
        </tr>

        <tr>
            <td></td>
            <!-- Water pump constant on -->
            <td onmousedown='onTouchStartAndEnd("10")' ontouchstart='onTouchStartAndEnd("10")' class="button"><span class="waterSymbols" >ON</span></td>
            <!-- Water pump constant of -->
            <td onmousedown='onTouchStartAndEnd("10")' ontouchstart='onTouchStartAndEnd("10")' onmouseup='onTouchStartAndEnd("11")' ontouchend='onTouchStartAndEnd("11")' class="button"><span class="waterSymbols" >&#128167;</span></td>
            <!-- Water pump constant of -->
            <td onmousedown='onTouchStartAndEnd("11")' ontouchstart='onTouchStartAndEnd("11")' class="button"><span class="waterSymbols" >OFF</span></td>
            <td></td>
        </tr>

    </table>

    <script>

        console.log("disable default event listener");
        console.log("");

        document.getElementById("driveTable").addEventListener("touchend", function(event){
                event.preventDefault()
            });

        document.getElementById("turretTable").addEventListener("touchend", function(event){
                event.preventDefault()
            });

        document.getElementById("actuatorTable").addEventListener("touchend", function(event){
                event.preventDefault()
            });

        document.getElementById("pumpTable").addEventListener("touchend", function(event){
                event.preventDefault()
            });

        initWebSocket();  
        
       
        console.log("Ready");
        console.log("");     
    </script>
    
  </body>
</html> 
)HTMLHOMEPAGE";