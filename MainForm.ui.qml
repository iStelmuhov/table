import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtGraphicalEffects 1.0


Item{
    id:root
    width:800
    height:400

    Connections {
        target: programmModel
        onActiveChanged: {

            horizontalList.model=programmModel.active.list

        }
    }
    Connections {
        target: programmModel
        onListChanged: {
            groupList.model=programmModel.gropsList
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

    RowLayout
    {
        anchors.fill: parent
        anchors.top:parent.top
        anchors.left: parent.left
        height: root.height
        width:root.width
        id:row

        Rectangle
        {
            id:groupListRect

            anchors.top: row.top
            anchors.bottom: row.bottom

            height:row.height
            width:groupList.width
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
                    sourceRect: Qt.rect(0, 0, groupList.width, groupList.height)
                }
            }

            ListView
            {

                id:groupList
                z:5
                width:row.width/5
                height:row.height
                highlight: highlightComponent
                model:programmModel.gropsList
                spacing:3


                header:Rectangle{
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:row.width/5
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
                Text{
                    anchors.fill: parent;
                    verticalAlignment: Text.AlignVCenter;
                    horizontalAlignment: Text.AlignHCenter;
                    text: modelData.name
                }
                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled :true

                    onEntered: groupLittleButtons.opacity=1
                    onExited: groupLittleButtons.opacity=0
                    onClicked:{
                        groupList.currentIndex=index;
                        programmModel.getNewIndex(index);
                        horizontalList.currentIndex=programmModel.index-1;
                        horizontalList.positionViewAtIndex(programmModel.index-1,ListView.Right);
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
                            anchors.fill: parent
                            onClicked: console.log("!!!!");
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
                               onClicked: programmModel.deleteGroup(modelData.name);
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
        width:root.width+800
        model:programmModel.active.list
        orientation: ListView.Horizontal
        anchors.top:row.top
        anchors.bottom: row.bottom
        anchors.left:row.left
        cacheBuffer: 400
        snapMode: ListView.SnapToItem
        spacing: 3
        delegate:
            ListView{

            interactive: false
            id: verticalList
            width: row.width/5
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
                color:"orange"
                border.color: "#ffffff"
                border.width: 3
                z:3

                Text{
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text:modelData.dateTime
                }

            }
        }

        delegate:
            Rectangle{
            width: verticalList.width
            height:(root.height)/(programmModel.active.getNumberMax-programmModel.active.getNumberMin+1)-20
            color:modelData.color
            opacity: 0.6
            onWidthChanged:groupListRect.width=gaussBlur.width;
            Text{
                id: smallText
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter;
                horizontalAlignment: Text.AlignHCenter;
                elide: Text.ElideMiddle
                text: modelData.title
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked: {
                    console.log(programmModel.active.count)
                }

            }
        }
    }
}
}
}


