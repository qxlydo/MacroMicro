import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

ApplicationWindow {
    id: window

    visible: true
    width: 1100
    height: 720

    title: "MegaByteFinder — File Scanner"

    color: "#121212"

    property int minSizeMB: 100
    property int foundCount: 0
    property int displayedCount: 0
    property var foundFiles: []

    property double allWeightFiles: 0

    property bool scanning: false
    property string selectedFolderPath: ""
    property url selectedFolderUrl: ""

    function formatSize(bytes) {
        if (bytes < 1024)
            return bytes.toFixed(0) + " B"

        var kb = bytes / 1024

        if (kb < 1024)
            return kb.toFixed(2) + " KB"

        var mb = kb / 1024

        if (mb < 1024)
            return mb.toFixed(2) + " MB"

        var gb = mb / 1024

        return gb.toFixed(2) + " GB"
    }

    function rebuildLog() {

        foundFiles.sort(function(a, b) {
            return b.size - a.size
        })

        var visible = 0

        var logBuffer =
                "> Директория: " + selectedFolderPath + "\n" +
                "> Минимальный размер: " + minSizeMB + " MB\n\n" +
                "> Сортировка: от большего к меньшему\n\n"

        for (var i = 0; i < foundFiles.length; ++i) {
            var file = foundFiles[i]

            if (file.sizeMB >= minSizeMB) {
                logBuffer +=
                        "[FILE] " + file.path +
                        "    [" + formatSize(file.size) + "]\n"

                ++visible
            }
        }

        displayedCount = visible

        logBuffer +=
                "\n> Показано файлов: " + displayedCount + "\n" +
                "> Всего найдено: " + foundCount + "\n" +
                "> Общий вес файлов: " + formatSize(allWeightFiles) + "\n"

        terminal.text = logBuffer
    }

    Connections {
        target: engine

        function onScanStarted() {
            scanning = true

            foundFiles = []
            foundCount = 0
            displayedCount = 0
            allWeightFiles = 0

            terminal.text =
                    "> Начало сканирования\n" +
                    "> Директория: " + selectedFolderPath + "\n" +
                    "> Минимальный размер: " + minSizeMB + " MB\n\n"

            busyIndicator.running = true
        }

        function onFileFound(path, size) {

            var file = {
                path: path,
                size: size,
                sizeMB: size / (1024 * 1024)
            }

            foundFiles.push(file)
            allWeightFiles += size

            ++foundCount

            if (file.sizeMB >= minSizeMB) {

                terminal.append(
                            "[FILE] " +
                            file.path +
                            "    [" +
                            formatSize(file.size) +
                            "]"
                            )

                ++displayedCount
            }
        }

        function onScanFinished() {

            scanning = false
            busyIndicator.running = false

            rebuildLog()

            terminal.cursorPosition = terminal.length
        }

        function onError(msg) {

            scanning = false
            busyIndicator.running = false

            terminal.text +=
                    "\n[ERROR] " +
                    msg +
                    "\n"

            errorDialog.text = msg
            errorDialog.open()
        }
    }

    component DarkButton : Button {

        id: btn

        implicitHeight: 36

        contentItem: Text {
            text: btn.text
            font: btn.font

            color: btn.enabled
                   ? "#ffffff"
                   : "#666666"

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            elide: Text.ElideRight
        }

        background: Rectangle {

            color: !btn.enabled
                   ? "#1e1e1e"
                   : (
                         btn.down
                         ? "#111111"
                         : (
                               btn.hovered
                               ? "#383838"
                               : "#2a2a2a"
                           )
                     )

            radius: 6

            border.color: btn.enabled
                           ? "#444444"
                           : "#2c2c2c"

            border.width: 1
        }
    }

    ColumnLayout {

        anchors.fill: parent
        anchors.margins: 16

        spacing: 10

        RowLayout {

            Layout.fillWidth: true

            spacing: 8

            DarkButton {

                text: "📁 Выбрать папку"

                enabled: !scanning

                onClicked: {
                    folderDialog.open()
                }
            }

            Label {

                id: selectedPathLabel

                text: selectedFolderPath === ""
                      ? "Папка не выбрана"
                      : selectedFolderPath

                color: selectedFolderPath === ""
                       ? "#888888"
                       : "#ffffff"

                Layout.fillWidth: true

                elide: Text.ElideMiddle
            }

            DarkButton {

                text: "▶ Начать поиск"

                enabled:
                    selectedFolderUrl.toString() !== "" &&
                    !scanning

                onClicked: {
                    engine.scanDirectory(selectedFolderUrl)
                }
            }

            DarkButton {

                text: "Очистить"

                enabled: !scanning

                onClicked: {

                    terminal.text =
                            "> Выберите папку и нажмите «Начать поиск»...\n"

                    foundFiles = []
                    foundCount = 0
                    displayedCount = 0

                    // Сбрасываем общий вес
                    allWeightFiles = 0

                    engine.clearFiles()
                }
            }
        }

        RowLayout {

            Layout.fillWidth: true

            spacing: 8

            Label {

                text: "Показывать файлы размером от:"

                color: "#ffffff"
            }

            ComboBox {

                id: sizeComboBox

                model: [
                    "Все файлы",
                    "≥ 10 MB",
                    "≥ 50 MB",
                    "≥ 100 MB",
                    "≥ 500 MB",
                    "≥ 1 GB",
                    "≥ 5 GB",
                    "≥ 10 GB"
                ]

                currentIndex: 3

                contentItem: Text {

                    text: sizeComboBox.displayText

                    color: "#ffffff"

                    verticalAlignment:
                        Text.AlignVCenter

                    leftPadding: 10
                }

                background: Rectangle {

                    color: "#2a2a2a"

                    radius: 6

                    border.color: "#444444"
                }

                onCurrentIndexChanged: {

                    switch (currentIndex) {

                    case 0:
                        minSizeMB = 0
                        break

                    case 1:
                        minSizeMB = 10
                        break

                    case 2:
                        minSizeMB = 50
                        break

                    case 3:
                        minSizeMB = 100
                        break

                    case 4:
                        minSizeMB = 500
                        break

                    case 5:
                        minSizeMB = 1024
                        break

                    case 6:
                        minSizeMB = 5120
                        break

                    case 7:
                        minSizeMB = 10240
                        break
                    }

                    if (foundFiles.length > 0 && !scanning) {
                        rebuildLog()
                    }
                }
            }

            Label {

                text: "Всего: " + foundCount

                color: "#aaaaaa"
            }

            Label {

                text: "Показано: " + displayedCount

                color: "#aaaaaa"
            }

            Label {

                text:
                    "Общий вес: " +
                    formatSize(allWeightFiles)

                color: "#aaaaaa"
            }

            Item {
                Layout.fillWidth: true
            }

            BusyIndicator {

                id: busyIndicator

                running: false
            }

            Label {

                text: engine.status

                color: "#aaaaaa"

                Layout.maximumWidth: 300

                elide: Text.ElideRight
            }
        }

        Rectangle {

            Layout.fillWidth: true
            Layout.fillHeight: true

            color: "#111111"

            radius: 8

            border.color: "#333333"

            ScrollView {

                id: terminalScroll

                anchors.fill: parent

                anchors.margins: 8

                TextArea {

                    id: terminal

                    width:
                        Math.max(
                            parent.width,
                            terminal.contentWidth
                        )

                    height:
                        Math.max(
                            parent.height,
                            terminal.contentHeight
                        )

                    readOnly: true

                    selectByMouse: true

                    text:
                        "> Выберите папку и нажмите «Начать поиск»...\n"

                    font.family: "Consolas"

                    font.pixelSize: 14

                    color: "#dddddd"

                    selectionColor: "#444444"

                    wrapMode: TextEdit.NoWrap

                    background: null

                    onTextChanged: {
                        cursorPosition = length
                    }
                }
            }
        }
    }

    FolderDialog {

        id: folderDialog

        title: "Выберите папку"

        onAccepted: {

            selectedFolderUrl = selectedFolder

            selectedFolderPath =
                    selectedFolder.toString()

            if (selectedFolderPath.startsWith("file:///")) {

                selectedFolderPath =
                        decodeURIComponent(
                            selectedFolderPath.substring(8)
                        )
            }

            terminal.text =
                    "> Папка выбрана:\n" +
                    selectedFolderPath +
                    "\n\n" +
                    "> Выберите минимальный размер " +
                    "и нажмите «Начать поиск»...\n"
        }
    }

    MessageDialog {

        id: errorDialog

        title: "Ошибка"
    }
}
