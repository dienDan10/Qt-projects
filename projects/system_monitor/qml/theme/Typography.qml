import QtQuick 2.15

QtObject {
    readonly property string familySans: "Inter"
    readonly property string familyMono: "Consolas"

    readonly property int weightLight: Font.Light
    readonly property int weightRegular: Font.Normal
    readonly property int weightMedium: Font.Medium
    readonly property int weightSemiBold: Font.DemiBold
    readonly property int weightBold: Font.Bold

    // Display
    readonly property int displayLargePixelSize: 57
    readonly property int displayLargeWeight: weightRegular
    readonly property real displayLargeLineHeight: 1.12
    readonly property real displayLargeLetterSpacing: -0.25

    readonly property int displayMediumPixelSize: 45
    readonly property int displayMediumWeight: weightRegular
    readonly property real displayMediumLineHeight: 1.15
    readonly property real displayMediumLetterSpacing: 0.0

    // Headline
    readonly property int headlineLargePixelSize: 32
    readonly property int headlineLargeWeight: weightRegular
    readonly property real headlineLargeLineHeight: 1.2
    readonly property real headlineLargeLetterSpacing: 0.0

    readonly property int headlineMediumPixelSize: 28
    readonly property int headlineMediumWeight: weightRegular
    readonly property real headlineMediumLineHeight: 1.25
    readonly property real headlineMediumLetterSpacing: 0.0

    // Title
    readonly property int titleLargePixelSize: 22
    readonly property int titleLargeWeight: weightRegular
    readonly property real titleLargeLineHeight: 1.27
    readonly property real titleLargeLetterSpacing: 0.0

    readonly property int titleMediumPixelSize: 16
    readonly property int titleMediumWeight: weightMedium
    readonly property real titleMediumLineHeight: 1.5
    readonly property real titleMediumLetterSpacing: 0.1

    // Body
    readonly property int bodyLargePixelSize: 16
    readonly property int bodyLargeWeight: weightRegular
    readonly property real bodyLargeLineHeight: 1.5
    readonly property real bodyLargeLetterSpacing: 0.1

    readonly property int bodyMediumPixelSize: 14
    readonly property int bodyMediumWeight: weightRegular
    readonly property real bodyMediumLineHeight: 1.43
    readonly property real bodyMediumLetterSpacing: 0.25

    readonly property int bodySmallPixelSize: 12
    readonly property int bodySmallWeight: weightRegular
    readonly property real bodySmallLineHeight: 1.33
    readonly property real bodySmallLetterSpacing: 0.4

    // Label
    readonly property int labelLargePixelSize: 14
    readonly property int labelLargeWeight: weightMedium
    readonly property real labelLargeLineHeight: 1.43
    readonly property real labelLargeLetterSpacing: 0.1

    readonly property int labelMediumPixelSize: 12
    readonly property int labelMediumWeight: weightMedium
    readonly property real labelMediumLineHeight: 1.33
    readonly property real labelMediumLetterSpacing: 0.5

    readonly property int labelSmallPixelSize: 11
    readonly property int labelSmallWeight: weightMedium
    readonly property real labelSmallLineHeight: 1.45
    readonly property real labelSmallLetterSpacing: 0.5

    // Semantic aliases
    readonly property int appTitlePixelSize: titleLargePixelSize
    readonly property int appTitleWeight: titleLargeWeight
    readonly property real appTitleLineHeight: titleLargeLineHeight
    readonly property real appTitleLetterSpacing: titleLargeLetterSpacing

    readonly property int sectionTitlePixelSize: titleMediumPixelSize
    readonly property int sectionTitleWeight: titleMediumWeight
    readonly property real sectionTitleLineHeight: titleMediumLineHeight
    readonly property real sectionTitleLetterSpacing: titleMediumLetterSpacing

    readonly property int bodyPixelSize: bodyMediumPixelSize
    readonly property int bodyWeight: bodyMediumWeight
    readonly property real bodyLineHeight: bodyMediumLineHeight
    readonly property real bodyLetterSpacing: bodyMediumLetterSpacing

    readonly property int captionPixelSize: bodySmallPixelSize
    readonly property int captionWeight: bodySmallWeight
    readonly property real captionLineHeight: bodySmallLineHeight
    readonly property real captionLetterSpacing: bodySmallLetterSpacing

    readonly property int buttonPixelSize: labelLargePixelSize
    readonly property int buttonWeight: labelLargeWeight
    readonly property real buttonLineHeight: labelLargeLineHeight
    readonly property real buttonLetterSpacing: labelLargeLetterSpacing

    readonly property int codePixelSize: 13
    readonly property int codeWeight: weightRegular
    readonly property real codeLineHeight: 1.38
    readonly property real codeLetterSpacing: 0.0
}