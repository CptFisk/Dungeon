function Interact(monster)
    local state = monster:GetState()

    if(state == ObjectState.IDLE) then

        --Calculate distances
        local mx,my = monster:GetCenter()
        local px,py = GetPlayerCenter()
        local dist = GetDistance(mx,my,px,py)
        if(dist < 3) then
            monster:SetState(ObjectState.MOVE)
            --monster:GetRetain("Reload") == 0 and
        elseif(dist > 3 and dist < 5) then
            print("Pow pow pow")
            monster:SetState(ObjectState.ATTACK)
        end
    elseif state == ObjectState.MOVE then
        --Calculate distances
        local mx,my = monster:GetCenter()
        local px,py = GetPlayerCenter()
        local dist = GetDistance(mx,my,px,py)
        if(dist > 4.5) then
            monster:SetState(ObjectState.IDLE)
        else
            local angle = GetAngle(mx,my, px,py)
            local x,y = GetVector(angle, monster:GetVelocity())
            if(CheckObstacle(mx+x, my+y)) then
                monster:MoveAngle(angle, monster:GetVelocity())
            end
        end
    elseif state == ObjectState.ATTACK then
        ProjectileEnemy("Texture", "Effect", 3.0, 4.0, 5.0, 6.0,7.0, 8.0)
    end
end
