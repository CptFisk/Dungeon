function Interact(monster)
    local state = monster:GetState()

    if(state == ObjectState.IDLE) then

        --Calculate distances
        local mx,my = monster:GetCenter()
        local px,py = GetPlayerCenter()
        local dist = GetDistance(mx,my,px,py)
        if(dist <= 8) then
            monster:SetState(ObjectState.MOVE)
        end
    elseif state == ObjectState.MOVE then
        --Calculate distances
        local mx,my = monster:GetCenter()
        local px,py = GetPlayerCenter()
        local dist = GetDistance(mx,my,px,py)
        if(dist > 8) then
            monster:SetState(ObjectState.IDLE)
        else
            local angle = GetAngle(px,py, mx,my)
            local x,y = GetVector(angle, monster:GetVelocity())
            print(x)
            print(y)
            if(CheckObstacle(mx+x, my+y)) then
                monster:MoveAngle(angle, monster:GetVelocity())
            end
        end
    end
end
