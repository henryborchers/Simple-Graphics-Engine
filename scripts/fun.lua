--
-- Created by IntelliJ IDEA.
-- User: hborcher
-- Date: 2/4/17
-- Time: 3:34 PM
-- To change this template use File | Settings | File Templates.
--


local engine = require "libgengine"

print("loaded engine library")

function update_velocity(current_speed, value)
    if value >= 255 then
        return -1
    end

    if value <= 0 then
        return 1
    end
    return current_speed
end

print("Creating new window")
local window = engine.window.new(640, 480, "My Window")
local color = { r, g, b, a }
local v_color = { r, g, b, a }
local top_right_pane = window:createPane(320, 240)
local top_left_pane = window:createPane(320, 240)
local bottom_left_pane = window:createPane(320, 240)
local bottom_right_pane = window:createPane(320, 240)


top_left_pane:setOrientation(0, 0)
top_left_pane:setColor(0, 255, 127, 127)
top_right_pane:setOrientation(319, 0)
top_right_pane:setColor(127, 0, 127, 127)
bottom_left_pane:setOrientation(319, 239)
bottom_left_pane:setColor(255, 0, 127, 127)
bottom_right_pane:setOrientation(0, 239)
bottom_right_pane:setColor(0, 0, 127, 127)

while window:mainloop() do
end

print("All done")