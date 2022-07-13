#pragma once

#include "Frame.h"
#include "Text.h"

class Font;

class MainShader;

namespace gui
{

class TextLine : public Frame
{
public:
    enum class Align
    {
        Start,
        End,
        Center
    };

public:
    TextLine() = default;
    ~TextLine() = default;
    TextLine( const TextLine& ) = delete;
    TextLine( TextLine&& ) = delete;
    TextLine& operator=( const TextLine& ) = delete;
    TextLine& operator=( TextLine&& ) = delete;

    void setFont( Font& font ) noexcept;
    const Font* getFont() const noexcept;

    const std::string& getString() const;
    void setString( const std::string& string ) noexcept;

    void setFontSize( float size ) noexcept;
    float getFontSize() const noexcept;

    void setColor( RGB color ) noexcept;
    RGB getColor() const noexcept;

    void draw( GuiShader& guiShader, MainShader& textShader );

    Align getTextHorizontalAlign() const noexcept;
    void setTextHorizontalAlign( Align textHorizontalAlign ) noexcept;
    Align getTextVerticalAlign() const noexcept;
    void setTextVerticalAlign( Align textVerticalAlign ) noexcept;

private:
    void recalculateTextData() noexcept;

private:
    Text text_;
    Align textHorizontalAlign_ = Align::Start;
    Align textVerticalAlign_ = Align::Start;
};

} // namespace gui