import QtQuick

QtObject {
    id: focusRecommendations

    property var data: [
        {
            "level": 1,
            "minPercent": 81,
            "maxPercent": 100,
            "recommendationTitle": "How to keep it?",
            "focusPercentage": "100 - 80%",
            "arrowIconFileName": "arrowTop.png",
            "description": "High level of attention",
            "detailedDescription": "The mind works in a state of effective attention.",
            "color": "#299A13",
            "recommendations": [
                "It's worth taking regular, short regenerative breaks before fatigue sets in.",
                "Stay hydrated – drinking water helps maintain concentration.",
                "Gentle background music or white noise can support concentration."
            ]
        },
        {
            "level": 2,
            "minPercent": 41,
            "maxPercent": 80,
            "recommendationTitle": "How to change it?",
            "focusPercentage": "80 - 40%",
            "arrowIconFileName": "arrowStraight.png",
            "description": "Moderate level of concentration",
            "detailedDescription": "Attention is partially maintained but susceptible to distraction.",
            "color": "#A89519",
            "recommendations": [
                "Turn off notifications and put your phone away.",
                "Work in short sessions.",
                "Limit external stimuli and, if possible, change your environment.",
                // "Improve ergonomics: straighten your back and sit comfortably.",
                // "Short breathing exercises are recommended."
            ]
        },
        {
            "level": 3,
            "minPercent": 0,
            "maxPercent": 40,
            "recommendationTitle": "How to change it?",
            "focusPercentage": "40 - 0%",
            "arrowIconFileName": "arrowDown.png",
            "description": "Low level of attention",
            "detailedDescription": "Brain activity indicates reduced concentration of attention and dominance of external stimuli.",
            "color": "#841515",
            "recommendations": [
                "Take a short break, stretch, drink some water, and breathe deeply.",
                "A temporary change of scenery or a short walk may be helpful.",
                "If possible, reorganize the space around you – order means fewer distractions."
            ]
        }
    ]

    function byLevel(level) {
        for (var i = 0; i < data.length; ++i) {
            if (data[i].level === level)
                return data[i];
        }
        return data.length > 0 ? data[2] : null;
    }
}
