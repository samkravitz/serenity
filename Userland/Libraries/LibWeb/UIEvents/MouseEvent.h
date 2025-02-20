/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/TypeCasts.h>
#include <LibWeb/PixelUnits.h>
#include <LibWeb/UIEvents/EventModifier.h>
#include <LibWeb/UIEvents/UIEvent.h>

namespace Web::UIEvents {

struct MouseEventInit : public EventModifierInit {
    double offset_x = 0;
    double offset_y = 0;
    double client_x = 0;
    double client_y = 0;
    double page_x = 0;
    double page_y = 0;

    i16 button = 0;
    u16 buttons = 0;
};

class MouseEvent : public UIEvent {
    WEB_PLATFORM_OBJECT(MouseEvent, UIEvent);

public:
    [[nodiscard]] static JS::NonnullGCPtr<MouseEvent> create(JS::Realm&, FlyString const& event_name, MouseEventInit const& = {});
    static WebIDL::ExceptionOr<JS::NonnullGCPtr<MouseEvent>> create_from_platform_event(JS::Realm&, FlyString const& event_name, CSSPixelPoint offset, CSSPixelPoint client_offset, CSSPixelPoint page_offset, unsigned buttons, unsigned mouse_button = 1);

    virtual ~MouseEvent() override;

    double offset_x() const { return m_offset_x; }
    double offset_y() const { return m_offset_y; }

    double client_x() const { return m_client_x; }
    double client_y() const { return m_client_y; }

    // FIXME: Make these actually different from clientX and clientY.
    double screen_x() const { return m_client_x; }
    double screen_y() const { return m_client_y; }

    double page_x() const { return m_page_x; }
    double page_y() const { return m_page_y; }

    double x() const { return client_x(); }
    double y() const { return client_y(); }

    i16 button() const { return m_button; }
    u16 buttons() const { return m_buttons; }

    virtual u32 which() const override { return m_button + 1; }

protected:
    MouseEvent(JS::Realm&, FlyString const& event_name, MouseEventInit const& event_init);

    virtual void initialize(JS::Realm&) override;

private:
    void set_event_characteristics();

    double m_offset_x { 0 };
    double m_offset_y { 0 };
    double m_client_x { 0 };
    double m_client_y { 0 };
    double m_page_x { 0 };
    double m_page_y { 0 };
    i16 m_button { 0 };
    u16 m_buttons { 0 };
};

}
