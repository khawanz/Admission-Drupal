<?php

function list_konfirmasi_form(){
    global $base_url;
    $output = '';
    
    $output .= "<div style='padding-left:3px;border:1px solid #000000;width:80px;hight:100px;background-color:grey'>"
            . "<a style='text-decoration:none;color:black' href='$base_url/export-list-konfirmasi'>Export List</a>"
            . "</div>";
    
    $output .= views_embed_view('list_konfirmasi_pembayaran');
   
    return $output;
}
