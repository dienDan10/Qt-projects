pragma Singleton
import QtQuick 2.15

QtObject {
    property bool darkMode: false

    readonly property QtObject current: darkMode ? darkPalette : lightPalette
    readonly property QtObject spacing: spacingTokens
    readonly property QtObject typography: typographyTokens

    property DarkPalette darkPalette: DarkPalette {}
    property LightPalette lightPalette: LightPalette {}
    property Spacing spacingTokens: Spacing {}
    property Typography typographyTokens: Typography {}
}
