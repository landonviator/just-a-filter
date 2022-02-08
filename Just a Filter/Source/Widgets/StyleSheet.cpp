/*
  ==============================================================================

    StyleSheet.cpp
    Created: 20 Jul 2021 6:38:58pm
    Author:  landon viator

  ==============================================================================
*/

#include "StyleSheet.h"

namespace juce
{
    void LV_CustomAbleDialLAF::drawRotarySlider (Graphics& g,
                                                 int x,
                                                 int y,
                                                 int width,
                                                 int height,
                                                 float sliderPos,
                                                 const float rotaryStartAngle,
                                                 const float rotaryEndAngle,
                                                 Slider& slider)
    {
        auto outline = slider.findColour (Slider::rotarySliderOutlineColourId);
        auto bounds = Rectangle<int> (x, y, width, height).toFloat().reduced (10);
        auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = jmin (4.0f, radius * 0.5f);
        auto arcRadius = radius - lineW * 0.5f;

        // Dial-path background
        Path backgroundArc;
        backgroundArc.addCentredArc (bounds.getCentreX(),
                                     bounds.getCentreY(),
                                     arcRadius,
                                     arcRadius,
                                     0.0f,
                                     rotaryStartAngle,
                                     rotaryEndAngle,
                                     true);

        g.setColour (outline);
        g.strokePath (backgroundArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));

        if (slider.isEnabled())
        {
            // Part of arc that is filled (values that have been passed)
            Path valueArc;
            
            valueArc.addCentredArc (bounds.getCentreX(),
                                    bounds.getCentreY(),
                                    arcRadius,
                                    arcRadius,
                                    0.0f,
                                    rotaryStartAngle * stereoDialScalar,
                                    toAngle,
                                    true);

            g.setColour (slider.findColour(Slider::rotarySliderFillColourId));
            g.strokePath (valueArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
        }

        // Dial thumb
        Point<float> thumbPoint (bounds.getCentreX() + (arcRadius - lineW * 1.25) * std::cos (toAngle - MathConstants<float>::halfPi),
                                 bounds.getCentreY() + (arcRadius - lineW * 1.25) * std::sin (toAngle - MathConstants<float>::halfPi));

        g.setColour (slider.findColour(Slider::thumbColourId));
        g.drawLine(backgroundArc.getBounds().getCentreX(), backgroundArc.getBounds().getCentreY(), thumbPoint.getX(), thumbPoint.getY(), lineW / 2.0);
    }

    void LV_CustomAbleDialLAF::setDialIsStereoDial(bool isStereoDial)
    {
        if (isStereoDial)
        {
            stereoDialScalar = 1.67;
        }
        
        else
        {
            stereoDialScalar = 1.0;
        }
    }

/** Alpha Dial Style ====================================================================*/
void LV_AlphaDialLAF::drawRotarySlider(Graphics &g,
                                      int x,
                                      int y,
                                      int width,
                                      int height,
                                      float sliderPos,
                                      float rotaryStartAngle,
                                      float rotaryEndAngle,
                                      Slider &slider)
{
    
    float diameter = fmin(width, height) * .7;
    float radius = diameter * 0.5;
    float centerX = x + width * 0.5;
    float centerY = y + height * 0.5;
    float rx = centerX - radius;
    float ry = centerY - radius;
    float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));
                    
    Rectangle<float> dialArea (rx, ry, diameter, diameter);
    g.setColour(slider.findColour(Slider::thumbColourId)); //center
    g.fillEllipse(dialArea);
                    
    g.setColour(Colours::black.withAlpha(0.15f)); //outline
    g.drawEllipse(rx, ry, diameter, diameter, 10.0f);
    Path dialTick;
    g.setColour(Colours::whitesmoke.darker(0.5)); //tick color
    dialTick.addRectangle(0, -radius + 6, 3.0f, radius * 0.6);
    g.fillPath(dialTick, AffineTransform::rotation(angle).translated(centerX, centerY));
}

void LV_AlphaDialLAF::drawLabel(Graphics &g, Label &label)
{
    g.fillAll (label.findColour (Label::backgroundColourId));

    if (! label.isBeingEdited())
    {
        auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        const Font font (juce::Font ("Helvetica", 12.0f, juce::Font::FontStyleFlags::plain));

        g.setColour (label.findColour (Label::textColourId).withMultipliedAlpha (alpha));
        g.setFont (font);

        auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());

        g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                          jmax (1, (int) ((float) textArea.getHeight() / font.getHeight())),
                          label.getMinimumHorizontalScale());

        g.setColour (label.findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
    }
    
    else if (label.isEnabled())
    {
        g.setColour (label.findColour (Label::outlineColourId));
    }

    g.drawRect (label.getLocalBounds());
}

    /** Hard Dial Style ====================================================================*/
    void LV_HardDialLAF::drawRotarySlider(Graphics &g,
                                          int x,
                                          int y,
                                          int width,
                                          int height,
                                          float sliderPos,
                                          float rotaryStartAngle,
                                          float rotaryEndAngle,
                                          Slider &slider)
    {
        float diameter = fmin(width, height) * .9;
        float radius = diameter * 0.5;
        float centerX = x + width * 0.5;
        float centerY = y + height * 0.5;
        float rx = centerX - radius;
        float ry = centerY - radius;
        float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));
                
        juce::Rectangle<float> dialArea (rx, ry, diameter, diameter);
        g.setColour(slider.findColour(Slider::thumbColourId).withAlpha(0.7f)); //center
        g.fillEllipse(dialArea);
        
        g.setColour(slider.findColour(juce::Slider::ColourIds::rotarySliderOutlineColourId)); //outline
        g.drawEllipse(rx, ry, diameter, diameter, 4.0f);
        juce::Path dialTick;
        g.setColour(slider.findColour(juce::Slider::ColourIds::trackColourId)); //tick color
        dialTick.addRectangle(0, -radius + 2, 4.0f, radius * 0.6);
        g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centerX, centerY));
    }

    void LV_HardDialLAF::drawLabel(Graphics &g, Label &label)
    {
        g.fillAll (label.findColour (Label::backgroundColourId));

        if (! label.isBeingEdited())
        {
            auto alpha = label.isEnabled() ? 1.0f : 0.5f;
            const Font font (juce::Font ("Helvetica", 16.0f, juce::Font::FontStyleFlags::bold));

            g.setColour (label.findColour (Label::textColourId).withMultipliedAlpha (alpha));
            g.setFont (font);

            auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());

            g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                              jmax (1, (int) ((float) textArea.getHeight() / font.getHeight())),
                              label.getMinimumHorizontalScale());

            g.setColour (label.findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
        }
        
        else if (label.isEnabled())
        {
            g.setColour (label.findColour (Label::outlineColourId));
        }

        g.drawRect (label.getLocalBounds());
    }

    /** FADER Styles ====================================================================*/
    void LV_FaderLAF::drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                           float sliderPos,
                                           float minSliderPos,
                                           float maxSliderPos,
                                           const Slider::SliderStyle style, Slider& slider)
    {
        if (slider.isBar())
        {
            g.setColour (slider.findColour (Slider::trackColourId));
            g.fillRect (slider.isHorizontal() ? Rectangle<float> (static_cast<float> (x), (float) y + 0.5f, sliderPos - (float) x, (float) height - 1.0f)
                                              : Rectangle<float> ((float) x + 0.5f, sliderPos, (float) width - 1.0f, (float) y + ((float) height - sliderPos)));
        }
        
        else
        {
            auto isTwoVal   = (style == Slider::SliderStyle::TwoValueVertical   || style == Slider::SliderStyle::TwoValueHorizontal);
            auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

            auto trackWidth = jmin (9.0f, slider.isHorizontal() ? (float) height * 0.25f : (float) width * 0.25f);

            Point<float> startPoint (slider.isHorizontal() ? (float) x : (float) x + (float) width * 0.5f,
                                     slider.isHorizontal() ? (float) y + (float) height * 0.5f : (float) (height + y));

            Point<float> endPoint (slider.isHorizontal() ? (float) (width + x) : startPoint.x,
                                   slider.isHorizontal() ? startPoint.y : (float) y);

            Path backgroundTrack;
            backgroundTrack.startNewSubPath (startPoint);
            backgroundTrack.lineTo (endPoint);
            g.setColour (slider.findColour (Slider::backgroundColourId));
            g.strokePath (backgroundTrack, { static_cast<float>(trackWidth * 1.25), PathStrokeType::curved, PathStrokeType::rounded });

            Path valueTrack;
            Point<float> minPoint, maxPoint, thumbPoint;

            if (isTwoVal || isThreeVal)
            {
                minPoint = { slider.isHorizontal() ? minSliderPos : (float) width * 0.5f,
                             slider.isHorizontal() ? (float) height * 0.5f : minSliderPos };

                if (isThreeVal)
                    thumbPoint = { slider.isHorizontal() ? sliderPos : (float) width * 0.5f,
                                   slider.isHorizontal() ? (float) height * 0.5f : sliderPos };

                maxPoint = { slider.isHorizontal() ? maxSliderPos : (float) width * 0.5f,
                             slider.isHorizontal() ? (float) height * 0.5f : maxSliderPos };
            }
            
            else
            {
                auto kx = slider.isHorizontal() ? sliderPos : ((float) x + (float) width * 0.5f);
                auto ky = slider.isHorizontal() ? ((float) y + (float) height * 0.5f) : sliderPos;

                minPoint = startPoint;
                maxPoint = { kx, ky };
            }

            valueTrack.startNewSubPath (minPoint);
            valueTrack.lineTo (isThreeVal ? thumbPoint : maxPoint);
            g.setColour (slider.findColour (Slider::trackColourId));
            g.strokePath (valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

            if (! isTwoVal)
            {
                Rectangle<float> thumbRec;
                thumbRec.setSize(static_cast<float> (width / 2.0), static_cast<float> (width / 6.0));
                
                g.setColour(slider.findColour(Slider::thumbColourId));
                g.fillRoundedRectangle(thumbRec.withCentre(isThreeVal ? thumbPoint : maxPoint), 6.0f);
            }

            if (isTwoVal || isThreeVal)
            {
                auto sr = jmin (trackWidth, (slider.isHorizontal() ? (float) height : (float) width) * 0.4f);
                auto pointerColour = slider.findColour (Slider::thumbColourId);

                if (slider.isHorizontal())
                {
                    drawPointer (g, minSliderPos - sr,
                                 jmax (0.0f, (float) y + (float) height * 0.5f - trackWidth * 2.0f),
                                 trackWidth * 2.0f, pointerColour, 2);

                    drawPointer (g, maxSliderPos - trackWidth,
                                 jmin ((float) (y + height) - trackWidth * 2.0f, (float) y + (float) height * 0.5f),
                                 trackWidth * 2.0f, pointerColour, 4);
                }
                
                else
                {
                    drawPointer (g, jmax (0.0f, (float) x + (float) width * 0.5f - trackWidth * 2.0f),
                                 minSliderPos - trackWidth,
                                 trackWidth * 2.0f, pointerColour, 1);

                    drawPointer (g, jmin ((float) (x + width) - trackWidth * 2.0f, (float) x + (float) width * 0.5f), maxSliderPos - sr,
                                 trackWidth * 2.0f, pointerColour, 3);
                }
            }
        }
    }

    void LV_FaderLAF::drawLabel (Graphics& g, Label& label)
    {
        g.fillAll (label.findColour (Label::backgroundColourId));

        if (! label.isBeingEdited())
        {
            auto alpha = label.isEnabled() ? 1.0f : 0.5f;
            const Font font (juce::Font (sliderFont, 12.0f, juce::Font::FontStyleFlags::bold));

            g.setColour (label.findColour (Label::textColourId).withMultipliedAlpha (alpha));
            g.setFont (font);

            auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());

            g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                              jmax (1, (int) ((float) textArea.getHeight() / font.getHeight())),
                              label.getMinimumHorizontalScale());

            g.setColour (label.findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
        }
        
        else if (label.isEnabled())
        {
            g.setColour (label.findColour (Label::outlineColourId));
        }

        g.drawRect (label.getLocalBounds());
    }

    /** Toggle Styles ====================================================================*/

    void LV_PhaseToggleLAF::drawToggleButton(juce::Graphics &g,
                                                   juce::ToggleButton &toggleButton,
                                                   bool shouldDrawButtonAsHighlighted,
                                                   bool shouldDrawButtonAsDown)
    {
        Path button;
                
        auto bounds = toggleButton.getLocalBounds();
                
        auto size = jmin(bounds.getWidth(), bounds.getHeight()) - 6;
        auto sr = bounds.withSizeKeepingCentre(size / 2.5, size / 2.5).toFloat();
        
        button.addEllipse(sr);
        
        button.startNewSubPath(sr.getX(), sr.getY() + sr.getHeight());
        button.lineTo(sr.getX() + sr.getWidth(), sr.getY());
                
        PathStrokeType pst(2.0f, PathStrokeType::JointStyle::curved);
                
        auto color =
        toggleButton.getToggleState() ? toggleButton.findColour(juce::ToggleButton::tickDisabledColourId) : toggleButton.findColour(juce::ToggleButton::tickColourId);
                
        g.setColour(color);
        g.strokePath(button, pst);
    }

void LV_PowerToggleLAF::drawToggleButton(juce::Graphics &g,
                                               juce::ToggleButton &toggleButton,
                                               bool shouldDrawButtonAsHighlighted,
                                               bool shouldDrawButtonAsDown)
{
    Path button;
            
    auto bounds = toggleButton.getLocalBounds();
            
    auto size = jmin(bounds.getWidth(), bounds.getHeight()) - 6;
    auto r = bounds.withSizeKeepingCentre(size, size).toFloat();
            
    float ang = 30.f;
            
    size -= 9;
    

    button.addCentredArc(r.getCentreX(),
                                r.getCentreY(),
                                size * 0.25,
                                size * 0.25,
                                0.f,
                                degreesToRadians(ang),
                                degreesToRadians(360.f - ang),
                                true);
            
    button.startNewSubPath(r.getCentreX(), r.getY() + r.getHeight() * 0.21);
    button.lineTo(r.getCentre());
            
    PathStrokeType pst(2.0f, PathStrokeType::JointStyle::curved);
            
    auto color =
    toggleButton.getToggleState() ? toggleButton.findColour(juce::ToggleButton::tickDisabledColourId) : toggleButton.findColour(juce::ToggleButton::tickColourId);
            
    g.setColour(color);
    g.strokePath(button, pst);
}

void LV_CustomBorder::drawGroupComponentOutline (Graphics& g, int width, int height,
                                                const String& text, const Justification& position,
                                                GroupComponent& group)
{
    const float textH = 24.0f;
    const float indent = 3.0f;
    const float textEdgeGap = 4.0f;
    auto cs = 5.0f;

    Font f (Font (juce::Font ("Helvetica", 24.0f, juce::Font::FontStyleFlags::bold)));

    Path p;
    auto x = indent;
    auto y = f.getAscent() - 3.0f;
    auto w = jmax (0.0f, (float) width - x * 2.0f);
    auto h = jmax (0.0f, (float) height - y  - indent);
    cs = jmin (cs, w * 0.5f, h * 0.5f);
    auto cs2 = 2.0f * cs;

    auto textW = text.isEmpty() ? 0
                                : jlimit (0.0f,
                                          jmax (0.0f, w - cs2 - textEdgeGap * 2),
                                          (float) f.getStringWidth (text) + textEdgeGap * 2.0f);
    auto textX = cs + textEdgeGap;

    if (position.testFlags (Justification::horizontallyCentred))
        textX = cs + (w - cs2 - textW) * 0.5f;
    else if (position.testFlags (Justification::right))
        textX = w - cs - textW - textEdgeGap;

    p.startNewSubPath (x + textX + textW, y);
    p.lineTo (x + w - cs, y);

    p.addArc (x + w - cs2, y, cs2, cs2, 0, MathConstants<float>::halfPi);
    p.lineTo (x + w, y + h - cs);

    p.addArc (x + w - cs2, y + h - cs2, cs2, cs2, MathConstants<float>::halfPi, MathConstants<float>::pi);
    p.lineTo (x + cs, y + h);

    p.addArc (x, y + h - cs2, cs2, cs2, MathConstants<float>::pi, MathConstants<float>::pi * 1.5f);
    p.lineTo (x, y + cs);

    p.addArc (x, y, cs2, cs2, MathConstants<float>::pi * 1.5f, MathConstants<float>::twoPi);
    p.lineTo (x + textX, y);

    auto alpha = group.isEnabled() ? 1.0f : 0.5f;

    g.setColour (group.findColour (GroupComponent::outlineColourId)
                    .withMultipliedAlpha (alpha));

    g.strokePath (p, PathStrokeType (3.0f));

    g.setColour (group.findColour (GroupComponent::textColourId)
                    .withMultipliedAlpha (alpha));
    g.setFont (f);
    g.drawText (text,
                roundToInt (x + textX), 6,
                roundToInt (textW),
                roundToInt (textH),
                Justification::centred, true);
}

}
