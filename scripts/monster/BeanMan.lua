function Interact(monster)
    local state = monster:GetState()
    local reload = monster:GetRetain("Reload")
    if (state == ObjectState.IDLE) then
        --Calculate distances
        local mx, my = monster:GetCenter()
        local px, py = GetPlayerCenter()
        local dist = GetDistance(mx, my, px, py)

        if (dist < 3) then
            monster:SetState(ObjectState.MOVE)
            --monster:GetRetain("Reload") == 0 and
        elseif (dist > 3 and dist < 5 and reload == 0) then
            monster:SetState(ObjectState.ATTACK)
            monster:SetRetain("Sequence", 30)
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
        local sequence = monster:GetRetain("Sequence")
        if(math.fmod(sequence, 10) == 0) then
            local mx, my = monster:GetCenter()
            local px, py = GetPlayerCenter()
            local angle = GetAngle(px, py, mx, my)
            local x,y =GetAngleDistance(mx,my, angle, 10)
            ProjectileEnemy("PurpleBall", "", x, y, angle, 50, 0.75, 10)
            if(sequence == 0) then
                monster:SetRetain("Reload", 100)
                monster:SetState(ObjectState.IDLE)
            end
        end
        monster:SetRetain("Sequence", math.max(0, sequence - 1))
    end
    monster:SetRetain("Reload", math.max(0, monster:GetRetain("Reload") - 1))
end
