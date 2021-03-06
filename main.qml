import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.2

ApplicationWindow {
    visible:true
    id:root
    width:800
    height:400
    title:"Khnure TimeTable"

Rectangle{
    id:layer0
    anchors.fill:parent
    Connections {
        target: programmModel
        onListChanged: {

            groupList.model=programmModel.gropsList
            groupList.currentIndex=groupList.activeIndex

        }
        onActiveChanged: {
            horizontalList.model=0
            horizontalList.model=programmModel.active.list
            horizontalList.currentIndex=programmModel.index;
            horizontalList.positionViewAtIndex(programmModel.index,ListView.Right);
        }
    }

    Component {
        id: highlightComponent

        Rectangle {
            z:11
            width: groupList.width
            height:50
            color: Qt.rgba(0, 0.57, 1, 0.3);
        }
    }

    Row
    {
        id:row
        anchors.fill: parent
        spacing: 0

        Rectangle
        {
            id:groupListRect

            anchors.top: row.top
            anchors.bottom: row.bottom

            height:row.height
            width:row.width/5

            opacity: 1
            color: "white"
            z:4

            GaussianBlur
            {
                id:gaussBlur
                anchors.fill: groupList
                radius:10
                samples:20
                deviation:4

                source: ShaderEffectSource {
                    sourceItem: horizontalList
                    sourceRect: Qt.rect(-groupList.width, 0, groupList.width, groupList.height)
                }
            }

            ListView
            {

                id:groupList
                z:5
                width:row.width/5
                height:row.height
                highlight: highlightComponent
                highlightFollowsCurrentItem:true
                highlightMoveVelocity : 1200
                model:programmModel.gropsList
                spacing:3
                 property int activeIndex :0;
                header:Rectangle{
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:groupList.width
                    height:50
                    z:3
                    color:Qt.rgba(0, 0, 0, 0.05)


                    Image{
                        anchors.centerIn: parent
                        width:50
                        height:50
                        source:"qrc:/new/ico/ico/add.png"
                    }

                    MouseArea
                    {
                        anchors.fill:parent
                        onClicked:
                        {
                           selectWindow.show()
                        }
                    }
                }

            delegate: Rectangle{

                width:parent.width
                height:45
                color: Qt.rgba(0, 0, 0, 0.1)
                Label{
                    anchors.fill: parent;
                    font.family: "Ubuntu"
                    font.pixelSize: 14
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter;
                    text: modelData.name
                }
                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled : true

                    onEntered: groupLittleButtons.opacity=1
                    onExited: groupLittleButtons.opacity=0
                    onClicked:{
                        groupList.activeIndex=index;
                        groupList.currentIndex=index;
                        programmModel.getNewIndex(modelData.name);

                    }
                }

               Component.onCompleted: height=(modelData.name==="") ? 0:45;

                RowLayout{
                    id:groupLittleButtons
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 5
                    height:13
                    width:30
                    opacity:0

                    Rectangle
                      {
                          id:updateButton
                          width:13
                          height:13
                          color: "transparent"

                          Image{
                               anchors.fill:parent
                               source:"qrc:/new/ico/ico/update.png"
                                width: 13
                                height: 13
                           }

                            MouseArea{
                            id:updateArea
                            anchors.fill: parent
                            onClicked: {
                                if(groupList.activeIndex==index)
                                    groupList.activeIndex=0
                                programmModel.update(modelData.name,modelData.id);
                                }
                            }

                        }

                     Rectangle
                       {
                           width:13
                           height:13

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
                                   if(groupList.activeIndex==index)
                                       groupList.activeIndex=0
                                   programmModel.deleteGroup(modelData.name);
                                }
                           }

                       }
                }


            }
        }

    }
    ListView
    {
        id:horizontalList
        height:root.height
        width:Screen.width
        model:programmModel.active.list
        orientation: ListView.Horizontal
        anchors.top:row.top
        anchors.bottom: row.bottom
        displayMarginBeginning: 600
        clip:true
        cacheBuffer: 600
        snapMode: ListView.SnapToItem
        antialiasing: true
        spacing: 3
        delegate:
            ListView{

            interactive: false
            id: verticalList
            width: row.width/5.1
            height: parent.height
            model: modelData.dayList
            spacing:3

            header:Component
            {
            Rectangle
            {
                id:verticalHeader
                width: verticalList.width
                height: 36
                color:Qt.rgba(0.1490,0.7373,1,0.7)
                border.color: "#ffffff"
                z:3

                Text{
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text:modelData.dateTimeString
                }

            }

        }

        delegate:
            Rectangle{
            id:lessonRect
            width: verticalList.width
            height:(root.height)/(programmModel.active.getNumberMax-programmModel.active.getNumberMin+1)-10
            color:modelData.color
            opacity: 0.6
            onWidthChanged:groupListRect.width=gaussBlur.width;

            Rectangle{
                id:pastRect
                anchors.fill: lessonRect
                color:Qt.rgba(0,0,0,0.3)
                    Component.onCompleted: {
                        pastRect.visible=(modelData.startTime<new Date()) ? 1:0;
                    }
            }

            Column{
                id:textColumn
                anchors.fill: parent
                clip:true
                spacing:5
            Label{
                id:brief
                width:parent.width
                horizontalAlignment: Text.AlignHCenter;
                elide: Text.ElideMiddle
                font.family: "Ubuntu"
                font.pixelSize: lessonRect.height/5
                text: modelData.brief
            }
            Label{
                width:parent.width
                horizontalAlignment: Text.AlignHCenter;
                font.family: "Ubuntu"
                font.pixelSize: lessonRect.height/5
                text:modelData.typeShort+', '+ modelData.auditory
            }
            Label{
                width:parent.width
                horizontalAlignment: Text.AlignHCenter;
                font.family: "Ubuntu"
                font.pixelSize: lessonRect.height/5
                text: modelData.lessonStartEndTime
                Component.onCompleted: textColumn.visible=(modelData.type===-1) ? 0:1;
            }
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked: {
                    if(textColumn.visible==1){
                    extendedInfoList.model=modelData;
                    extendedInfo.visible=true;
                    }
                }

            }
        }
    }
}
}
}
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
    ListView{
        id:extendedInfoList
        anchors.left:extendedInfo.horizontalCenter
        anchors.bottom:extendedInfo.verticalCenter
        anchors.bottomMargin:(root.height/2.5)/2
        anchors.leftMargin: -(root.width/2.5)/2
        delegate: Rectangle{

            id:extendedInfoBox
            border.width: 0.4
            height:root.height/2.5
            width:root.width/2.5

            visible:true
            color:modelData.color
            opacity: 0.6
            layer.enabled: true

            Column{
                anchors.fill: parent
                clip:true
                spacing:9
                Label{
                    font.bold: true
                    width:parent.width
                    opacity: 0.6
                    horizontalAlignment: Text.AlignHCenter;
                    elide: Text.ElideMiddle
                    font.family: "Ubuntu"
                    font.pixelSize: extendedInfoBox.height/11
                    text: modelData.title
                }
                Label{
                    width:parent.width
                    horizontalAlignment: Text.AlignHCenter;
                    font.family: "Ubuntu"
                    font.pixelSize: extendedInfoBox.height/11
                    text:modelData.typeFull+', '+ modelData.auditory
                }
                Label{
                    width:parent.width
                    horizontalAlignment: Text.AlignHCenter;
                    font.family: "Ubuntu"
                    font.pixelSize: extendedInfoBox.height/11
                    text: modelData.lessonStartEndTime
                }
                Label{
                    width:parent.width
                    horizontalAlignment: Text.AlignHCenter;
                    font.family: "Ubuntu"
                    fontSizeMode: Text.Fit;
                    minimumPixelSize: 10;
                    font.pixelSize: extendedInfoBox.height/11
                    text: modelData.teachersToString
                }
                Label{
                    width:parent.width
                    maximumLineCount:3
                    horizontalAlignment: Text.AlignHCenter;
                    font.family: "Ubuntu"
                    elide:Text.ElideMiddle
                    fontSizeMode: Text.Fit;
                    minimumPixelSize: 10;
                    font.pixelSize: extendedInfoBox.height/11
                    text: modelData.groupsToString
                }
            }
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
    }
    MouseArea{
        x:-groupListRect.width

        y:0
        height:root.height
        width: root.width
        onClicked: extendedInfo.visible=0;
    }
}
}


