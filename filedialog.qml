import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
FileDialog {
    id: fileDialog
    title: "Please choose a file"
    folder: shortcuts.home
    onAccepted: {
        console.log("You chose: " + fileDialog.fileUrl)
        DATAMGR._file_path=fileDialog.fileUrl
        fileDialog.destroy()
    }
    onRejected: {
        console.log("Canceled")
        fileurl=""
        fileDialog.destroy()
    }
    Component.onCompleted: visible = true
}
