select 
    *
FROM
    HOP_DONG
        left join
    CUA_PHONG ON HOP_DONG.ma_phong = CUA_PHONG.ma_phong
        LEFT JOIN
    TAI_SAN ON CUA_PHONG.ma_ts = TAI_SAN.ma_ts
WHERE HOP_DONG.MSSV = 'ct1056m012' 