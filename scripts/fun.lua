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
v_color.r = 1
v_color.g = 1
v_color.b = 1
v_color.a = 1
--print(window)
color.r = 0
color.g = 100
color.b = 200
color.a = 255


while window:mainloop() do

    v_color.r = update_velocity(v_color.r, color.r)
    v_color.g = update_velocity(v_color.g, color.g)
    v_color.b = update_velocity(v_color.b, color.b)
    v_color.a = update_velocity(v_color.a, color.a)

    color.r = color.r + v_color.r
    color.g = color.g + v_color.g
    color.b = color.b + v_color.b
    color.a = color.a + v_color.a

    window:setcolor(color.r, color.g, color.b, color.a)
end

print("All done")