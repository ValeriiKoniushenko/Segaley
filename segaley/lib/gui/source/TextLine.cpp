#include "TextLine.h"

#include "Font.h"
#include "MainShader.h"

namespace gui
{

void TextLine::setFont( Font& font ) noexcept
{
    text_.setFont( font );
}

const Font* TextLine::getFont() const noexcept
{
    return text_.getFont();
}

const std::string& TextLine::getString() const
{
    return text_.getString();
}

void TextLine::setString( const std::string& string ) noexcept
{
    text_.setString( string );
}

void TextLine::setFontSize( float size ) noexcept
{
    text_.setSize( size );
}

float TextLine::getFontSize() const noexcept
{
    return text_.getSize();
}

void TextLine::setColor( RGB color ) noexcept
{
    text_.setColor( color );
}

RGB TextLine::getColor() const noexcept
{
    return text_.getColor();
}

void TextLine::draw( GuiShader& guiShader, MainShader& textShader )
{
    recalculateTextData();
    Frame::draw( guiShader );
    text_.draw( textShader );
}

void TextLine::recalculateTextData() noexcept
{
    text_.setPosition( getPosition() );

    if ( textHorizontalAlign_ == Align::Start )
        text_.move( { 0.f, 0.f } );
    if ( textHorizontalAlign_ == Align::Center )
        text_.move( { ( getSize().x - text_.getWidth() ) / 2.f, 0.f } );
    if ( textHorizontalAlign_ == Align::End )
        text_.move( { getSize().x - text_.getWidth(), 0.f } );

    if ( textVerticalAlign_ == Align::Start )
        text_.move( { 0.f, 0.f } );
    if ( textVerticalAlign_ == Align::Center )
        text_.move( { 0.f, ( getSize().y - text_.getSize() ) / -2.f } );
    if ( textVerticalAlign_ == Align::End )
        text_.move( { 0.f, ( getSize().y - text_.getSize() ) * -1.f } );
}

TextLine::Align TextLine::getTextHorizontalAlign() const noexcept
{
    return textHorizontalAlign_;
}

void TextLine::setTextHorizontalAlign( TextLine::Align textHorizontalAlign ) noexcept
{
    textHorizontalAlign_ = textHorizontalAlign;
}

TextLine::Align TextLine::getTextVerticalAlign() const noexcept
{
    return textVerticalAlign_;
}

void TextLine::setTextVerticalAlign( TextLine::Align textVerticalAlign ) noexcept
{
    textVerticalAlign_ = textVerticalAlign;
}

} // namespace gui
