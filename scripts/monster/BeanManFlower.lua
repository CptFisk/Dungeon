function Interact(monster)
    local state = monster:GetState()

    if (state == ObjectState.IDLE) then
        --Calculate distances
        local mx, my = monster:GetCenter()
        local px, py = GetPlayerCenter()
        local dist = GetDistance(mx, my, px, py)
        if (dist < 3) then
            monster:SetState(ObjectState.MOVE)
            --monster:GetRetain("Reload") == 0 and
        elseif (dist > 3 and dist < 5) then
            print("Pow pow pow")
            monster:SetState(ObjectState.ATTACK)
        end
    elseif state == ObjectState.MOVE then
        --Calculate distances
        local mx, my = monster:GetCenter()
        local px, py = GetPlayerCenter()
        local dist = GetDistance(mx, my, px, py)
        if (dist > 4.5) then
            monster:SetState(ObjectState.IDLE)
        else
            local angle = GetAngle(mx, my, px, py)
            local x, y = GetVector(angle, monster:GetVelocity())
            if (CheckObstacle(mx + x, my + y)) then
                monster:MoveAngle(angle, monster:GetVelocity())
            end
        end
    elseif state == ObjectState.ATTACK then
        local mx, my = monster:GetCenter()
        local px, py = GetPlayerCenter()
        local angle = GetAngle(px, py, mx, my)
        local x,y =GetAngleDistance(mx,my, angle, 10)
        for i = 0, 10 do
            ProjectileEnemy("PurpleBall", "", x, y, i * 20, 50, 0.75, 10)
        end
        monster:SetRetain("Reload", 100)
        monster:SetState(ObjectState.IDLE)
    end
    monster:SetRetain("Reload", math.max(0, monster:GetRetain("Reload") - 1))
end
