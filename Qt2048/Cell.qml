import QtQuick 2.0
import QtQuick.Controls 2.3

Item{
    property string txt: ""
    property color c: "#d4ccc4"
    property int xpos: 10
    property int ypos: 10
    property int scaleProp: 1
    z : zet()

    states: [
        State {
        name: "Empty"
        when: txt == ""
        }
    ]


    transitions: [
        Transition {
            from: "Empty"
            to: ""
            SequentialAnimation{
            PropertyAnimation{ easing.type: Easing.InOutBounce;properties: "scaleProp"; from: 1; to:1.2; duration:500}
            PropertyAnimation{ easing.amplitude: 1; easing.type: Easing.InOutElastic;properties: "scaleProp"; from: 1.2; to:1 ; duration:150}
            }
        }

    ]


    Behavior on xpos
    {
        SequentialAnimation{

            PauseAnimation {
                duration: pauseSpeed()
            }
            PropertyAnimation{ easing.type: easingType(); duration:animSpeed()}
        }
    }

    Behavior on ypos
    {
        SequentialAnimation{

            PauseAnimation {
                duration: pauseSpeed()
            }
            PropertyAnimation{ easing.type: easingType(); duration:animSpeed()}
        }
    }

    Behavior on c
    {

        ColorAnimation {
            duration: 100
        }
    }



    function animSpeed(){
        if (txt == "")
            return 0
        return 100
    }

    function pauseSpeed(){
        if (txt == "")
            return 0
        return 0
    }

    function easingType(){
        if (txt == "")
            return Easing.InBack
        return Easing.InSine
    }

    function zet(){
        if (txt == "")
            return 0
        return parseInt(txt)
    }


Rectangle {
    width: 75; height: 75
    color: c
    visible: true
    radius : 3
    scale : scaleProp
    anchors.top: parent.top
    anchors.left: parent.left
    Text{
        anchors.centerIn: parent
        text: txt
        font.family: "Helvetica"
        font.pointSize: 20
        color: "white"
    }


}

}
