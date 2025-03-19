import QtQuick 2.4
import QtQuick.Window 2.2

Item {
    visible: true
    width: 1280
    height: 720

    Rectangle{
        color :"black"
        anchors.fill: parent
    }


    Rectangle{
        anchors.fill: appliedFont
        border.color: "yellow"
        border.width: 2
        color:"transparent"
    }

    Row{
        id:parentRow
        anchors.fill: parent

    }

    Column{
        id:appliedFont
        parent:parentRow

        x:0
        anchors.top: parent.top
        anchors.topMargin: 30
        spacing: 10
        width: parent.width



//        Text{
//            text :"APPLIED FONT"
//            color:"white"
//            height: 50
//            font.pixelSize: 40
//        }

        Text{
            width: parent.width
            height: 20
            font.pixelSize: 18
            color:"white"
            text:"---------------------------------Bold fonts------------------------------------------------------------------------------------------------------------"
        }


        Row{
            width: parent.width

            Column{
                width: parent.width/4

                Text{
                    text: "English bold"
                    font.family: "Gotham Narrow Bold"
                    font.pixelSize: 20
                    color:"white"
                    height: font.pixelSize
                    renderType: Text.NativeRendering
                }

                Text{
                    text: "English bold"
                    font.family: "Gotham Narrow"
                    font.pixelSize: 20
                    font.bold: true
                    color:"white"
                    height: font.pixelSize
                    renderType: Text.NativeRendering
                }

                Text{
                    text: "English bold"
                    font.family: "Gotham Narrow"
                    font.pixelSize: 20
                    font.weight: Font.Bold
                    color:"white"
                    height: font.pixelSize
                    renderType: Text.NativeRendering
                }
            }

            Column{
                width: parent.width/4

                Text{
                    text: "مرحبا كيف حالك"
                    font.family: "beIN NEW Arabic font 2017 bold"
                    color:"white"
                    font.pixelSize: 20
                    renderType: Text.NativeRendering
                }

                Text{
                    text: "مرحبا كيف حالك"
                    font.family: "beIN NEW Arabic font 2017"
                    color:"white"
                    font.pixelSize: 20
                    font.bold: true
                    renderType: Text.NativeRendering
                }

                Text{
                    text: "مرحبا كيف حالك"
                    font.family: "beIN NEW Arabic font 2017"
                    color:"white"
                    font.pixelSize: 20
                    font.weight: Font.Bold
                    renderType: Text.NativeRendering
                }
            }
            Column{
                width: parent.width/4

                Text{
                    text: "Font family with name"
                    font.family: "beIN NEW Arabic font 2017 bold"
                    font.pixelSize: 20
                    color:"white"
                    height: font.pixelSize
                    renderType: Text.NativeRendering
                }

                Text{
                    text:"font family, font.bold:true"
                    font.family: "beIN NEW Arabic font 2017"
                    font.pixelSize: 20
                    font.bold: true
                    color:"white"
                    height: font.pixelSize
                    renderType: Text.NativeRendering
                }

                Text{
                    text:"font family, weight:Bold"
                    font.family: "beIN NEW Arabic font 2017"
                    font.pixelSize: 20
                    font.weight: Font.Bold
                    color:"white"
                    height: font.pixelSize
                    renderType: Text.NativeRendering
                }
            }


        }


        Text{
            width: parent.width
            height: 20
            font.pixelSize: 18
            color:"white"
            text:"---------------------------------Medium/demibold fonts------------------------------------------------------------------------------------------------------------"
        }


        //////////////////////////////////////////////////////////

        Row{
            width: parent.width

            Column{
                width: parent.width/4
                Text{
                    text: "English Medium Normal"
                    font.family: "Gotham Narrow Medium"
                    font.pixelSize: 20
                    color:"white"
                    height: font.pixelSize
                    renderType: Text.NativeRendering
                }

                Text{

                    text: "English Medium Normal"
                    font.family: "Gotham Narrow"
                    font.pixelSize: 20
                    color:"white"
                    height: font.pixelSize
                    font.weight: Font.DemiBold
                    renderType: Text.NativeRendering
                }
            }
            Column{
                width: parent.width/4
                Text{

                    text: "مرحبا كيف حالك"
                    font.family: "beIN NEW Arabic font 2017 DemiBd"
                    color:"white"
                    font.pixelSize: 20
                    renderType: Text.NativeRendering

                }

                Text{
                    text: "مرحبا كيف حالك"
                    font.family: "Gotham Narrow Medium"
                    color:"white"
                    font.pixelSize: 20
                    font.weight: Font.DemiBold
                    renderType: Text.NativeRendering
                }
            }
            Column{
                width: parent.width/4
                Text{
                    text: "Font family with name"
                    font.family: "beIN NEW Arabic font 2017 DemiBd"
                    font.pixelSize: 20
                    color:"white"
                    height: font.pixelSize
                    renderType: Text.NativeRendering
                }

                Text{

                    text:"font family, weight:DemiBold"
                    font.family: "beIN NEW Arabic font 2017"
                    font.pixelSize: 20
                    color:"white"
                    height: font.pixelSize
                    font.weight: Font.DemiBold
                    renderType: Text.NativeRendering
                }
            }

        }




        Text{
            width: parent.width
            height: 20
            font.pixelSize: 18
            color:"white"
            text:"---------------------------------Book regular fonts------------------------------------------------------------------------------------------------------------"
        }

        //////////////////////////////////////////////////////////

        Row{
            width: parent.width

            Column{
                width: parent.width/4
                Text{

                    text: "English Book"
                    font.family: "Gotham Narrow Book"
                    font.pixelSize: 20
                    color:"white"
                    height: font.pixelSize
                    renderType: Text.NativeRendering
                }
                Text{

                    text: "English Book"
                    font.family: "Gotham Narrow"
                    font.pixelSize: 20
                    color:"white"
                    height: font.pixelSize
                    renderType: Text.NativeRendering
                }
                Text{

                    text: "English Book"
                    font.family: "Gotham Narrow"
                    font.pixelSize: 20
                    color:"white"
                    height: font.pixelSize
                    font.weight: Font.Normal
                    renderType: Text.NativeRendering
                }
            }
            Column{
                width: parent.width/4
                Text{
                    text: "مرحبا كيف حالك"
                    font.family: "beIN NEW Arabic font 2017"
                    color:"white"
                    font.pixelSize: 20
                    renderType: Text.NativeRendering
                }
            }

            Column{
                width: parent.width/4
                Text{

                    text: "Font family with name"
                    font.family: "beIN NEW Arabic font 2017"
                    font.pixelSize: 20
                    color:"white"
                    height: font.pixelSize
                    renderType: Text.NativeRendering
                }
                Text{

                    text: "font family without weight"
                    font.family: "beIN NEW Arabic font 2017"
                    font.pixelSize: 20
                    color:"white"
                    height: font.pixelSize
                    renderType: Text.NativeRendering
                }
                Text{

                    text:"font family, weight:Normal"
                    font.family: "beIN NEW Arabic font 2017"
                    font.pixelSize: 20
                    color:"white"
                    height: font.pixelSize
                    font.weight: Font.Normal
                    renderType: Text.NativeRendering
                }
            }

        }




        Text{
            width: parent.width
            height: 20
            font.pixelSize: 18
            color:"white"
            text:"---------------------------------Light fonts------------------------------------------------------------------------------------------------------------"
        }

        //////////////////////////////////////////////////////////

        Row{
            width: parent.width

            Column{
                width: parent.width/4
                Text{
                    text: "English Light"
                    font.family: "Gotham Narrow Light"
                    font.pixelSize: 20
                    color:"white"

                    height: font.pixelSize
                    renderType: Text.NativeRendering
                }


                Text{
                    text: "English Light"
                    font.family: "Gotham Narrow"
                    font.pixelSize: 20
                    color:"white"
                    font.weight: Font.Light

                    height: font.pixelSize
                    renderType: Text.NativeRendering
                }
            }
            Column{
                width: parent.width/4
                Text{
                    text: "مرحبا كيف حالك"
                    font.family: "beIN NEW Arabic font 2017 Light"
                    color:"white"
                    font.pixelSize: 20
                    renderType: Text.NativeRendering
                }
                Text{
                    text: "مرحبا كيف حالك"
                    font.family: "beIN NEW Arabic font 2017"
                    color:"white"
                    font.pixelSize: 20
                    font.weight: Font.Light
                    renderType: Text.NativeRendering
                }
            }

            Column{
                width: parent.width/4
                Text{
                    text: "Font family with name"
                    font.family: "beIN NEW Arabic font 2017 Light"
                    color:"white"
                    font.pixelSize: 20
                    renderType: Text.NativeRendering
                }
                Text{
                    text:"font family, weight:light"
                    font.family: "beIN NEW Arabic font 2017"
                    color:"white"
                    font.pixelSize: 20
                    font.weight: Font.Light
                    renderType: Text.NativeRendering
                }
            }

        }



    }





}
