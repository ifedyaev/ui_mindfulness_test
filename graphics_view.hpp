#ifndef GRAPHICS_VIEW_HPP
#define GRAPHICS_VIEW_HPP

#include <QGraphicsView>
#include <stdint.h>

class GraphicsView : public QGraphicsView

{
public:
    GraphicsView( QWidget* parent )
        : QGraphicsView( parent )
    {
        setMouseTracking( true );
    }

    ~GraphicsView() {}

    void setViewRect( const QRectF& rect )
    {
        m_rect_to_resize = rect;

        const QRectF& unity = transform().mapRect( QRectF( 0.0, 0.0, 1.0, 1.0 ) );
        if ( unity.isEmpty() ) {
            return;
        }

        scale( 1.0 / unity.width(), 1.0 / unity.height() );

        const QRectF& viewRect = viewport()->rect();
        if ( viewRect.isEmpty() ) {
            return;
        }

        const QRectF& sceneRect = transform().mapRect( rect );
        if ( sceneRect.isEmpty() ) {
            return;
        }

        const qreal ratio = qMin( viewRect.width() / sceneRect.width(), viewRect.height() / sceneRect.height() );
        scale(ratio, ratio);

        centerOn( rect.center() );
    }

    QRectF viewRect() const
    {
        return viewportTransform().inverted().mapRect( QRectF( viewport()->rect() ) );
    }

private:
    void resizeEvent( QResizeEvent* event )
    {
        QGraphicsView::fitInView( m_rect_to_resize, Qt::KeepAspectRatio );
        QGraphicsView::resizeEvent( event );
    }

    QRectF m_rect_to_resize;
};

#endif // GRAPHICS_VIEW_HPP
