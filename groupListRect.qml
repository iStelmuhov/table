import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.2

Rectangle{

    x:groupListRect.width
    y:0
    width:root.width-groupListRect.width
    height:root.height
    id:extendedInfo
    color:"white"
    visible:false
    GaussianBlur
    {

      anchors.fill: parent
      radius:10
      samples:20
      deviation:4

        source: ShaderEffectSource {
            sourceItem: horizontalList
            sourceRect: Qt.rect(0, 0, extendedInfo.width, extendedInfo.height)
        }

    }
    Rectangle{


        x:root.width/8
        y:extendedInfo.height/4

        height:root.height/2.5
        width:root.width/2.5

        visible:true
        color:Qt.rgba(0, 0.4, 1, 0.6);

    MouseArea{
        anchors.fill: parent
        hoverEnabled : true
        onEntered: extendedInfoCross.opacity=1;
        onExited: extendedInfoCross.opacity=0;
    }
        Rectangle
          {
              id:extendedInfoCross
              anchors.right: parent.right
              anchors.top:parent.top
              anchors.topMargin: 4
              anchors.rightMargin: 4
              width:13
              height:13
              opacity: 0
              color: "transparent"
              Image{
                  anchors.fill:parent
                  source:"qrc:/new/ico/ico/delete.png"
                  width: 13
                  height: 13
              }

              MouseArea{
                  anchors.fill: parent
                  onClicked: {
                      extendedInfo.visible=0;
                   }
              }

          }

    }
    MouseArea{
        x:-groupListRect.width

        y:0
        height:root.height
        width: root.width
        onClicked: extendedInfo.visible=0;
    }
}
