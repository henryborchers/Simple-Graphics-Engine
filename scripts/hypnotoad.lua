--
-- Created by IntelliJ IDEA.
-- User: hborcher
-- Date: 2/4/17
-- Time: 3:34 PM
-- To change this template use File | Settings | File Templates.
--


local engine = require "libgengine"

print("loaded engine library")

local function create_eye(window, x, y)
    local line = window:createPane(104, 104)
    local white = window:createPane(100, 100)
    local iris = window:createPane(60, 60)
    local puple = window:createPane(50, 50)

    puple:setColor(0, 0, 0, 0)
    line:setColor(0, 0, 0, 0)
    white:setColor(154, 152, 50, 255)

    line:setOrientation(x - 2, y - 2)
    white:setOrientation(x, y)
    iris:setOrientation(x + 20, y + 20)
    puple:setOrientation(x + 25, y + 25)

    return { iris = iris, line = line, white = white, puple = puple }
end

function update_velocity(current_speed, value)
    if value >= 255 then
        return -1
    end

    if value <= 0 then
        return 1
    end
    return current_speed
end

print("Creating hynotoad!")
local window = engine.window.new(640, 480, "My Window")
local color = { r, g, b, a }
local v_color = { r, g, b, a }


local back = window:createPane(300, 150)
local head = window:createPane(300, 250)
local belly = window:createPane(280, 120)
local nose = window:createPane(300, 30)

local left_eye = create_eye(window, 150, 150)
local right_eye = create_eye(window, 400, 150)


head:setColor(154, 102, 0, 255)
back:setColor(154, 102, 0, 255)
belly:setColor(204, 152, 100, 255)
nose:setColor(124, 82, 0, 255)


head:setOrientation(180, 200)
nose:setOrientation(170, 290)
belly:setOrientation(185, 320)
back:setOrientation(285, 300)


--------------------
v_color.r = 1
v_color.g = 1
v_color.b = 1
v_color.a = 1

-- Initalize background color
color.r = 0
color.g = 100
color.b = 200
color.a = 255

while window:mainloop() do
    v_color.r = update_velocity(v_color.r, color.r)
    v_color.g = update_velocity(v_color.g, color.g)
    v_color.b = update_velocity(v_color.b, color.b)
    v_color.a = update_velocity(v_color.a, color.a)
    --    p:setOrientation(color.r, color.b)
    --    window:setColor(color.r,55,21, 55)

    color.r = color.r + v_color.r
    color.g = color.g + v_color.g
    color.b = color.b + v_color.b
    color.a = color.a + v_color.a
    right_eye.iris:setColor(color.r, color.g, color.b, color.a)
    left_eye.iris:setColor(color.r, color.g, color.b, color.a)
end

print("All done")