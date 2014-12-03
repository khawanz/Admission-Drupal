<?php


function admission_registered_export(){
    global $user;
       
    // Produce excel file..
  include_once libraries_get_path('phpexcel') . '/Classes/PHPExcel.php';

  $fname_date = 'daftar-pembayaran';
  
  $fname_ext = "xlsx";

  $output_path = variable_get('file_public_path', conf_path() . '/files')
      . "/" . $fname_date . "_" . $user->uid . "." . $fname_ext;
  // uid pada nama file untuk mengantisipasi multi user yg mendownlod pada waktu bersamaan
  // Create new PHPExcel object
  $objPHPExcel = new PHPExcel();

  $objPHPExcel->getProperties()->setCreator($user->name)
      ->setLastModifiedBy($user->name)
      ->setTitle("Laporan Pembayaran Mahasiswa")
      ->setSubject("Laporan Pembayaran Mahasiswa")
      ->setDescription("Laporan Pembayaran Mahasiswa")
      ->setKeywords("LaporanPembayaran Mahasiswa")
      ->setCategory("Laporan Pembayaran");

  // SHEET 0
  $objPHPExcel->setActiveSheetIndex(0);
  
  // SET WIDTH
  $objPHPExcel->getActiveSheet()->getColumnDimension('A')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('B')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('C')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('D')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('E')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('F')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('G')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('H')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('I')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('J')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('K')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('L')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('M')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('N')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('O')->setAutoSize(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('A1', 'NO. ');
  $objPHPExcel->getActiveSheet()->getStyle('A1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('A1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('B1', 'NO.REG.');
  $objPHPExcel->getActiveSheet()->getStyle('B1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('B1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('C1', 'NAMA');
  $objPHPExcel->getActiveSheet()->getStyle('C1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('C1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('D1', 'ASAL SEKOLAH');
  $objPHPExcel->getActiveSheet()->getStyle('D1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('D1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('E1', 'KAB/KOTA SEKOLAH');
  $objPHPExcel->getActiveSheet()->getStyle('E1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('E1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('F1', 'PROVINSI SEKOLAH');
  $objPHPExcel->getActiveSheet()->getStyle('F1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('F1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('G1', 'TELEPON');
  $objPHPExcel->getActiveSheet()->getStyle('G1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('G1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('H1', 'HP');
  $objPHPExcel->getActiveSheet()->getStyle('H1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('H1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('I1', 'TGL DAFTAR');
  $objPHPExcel->getActiveSheet()->getStyle('I1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('I1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('J1', 'EMAIL');
  $objPHPExcel->getActiveSheet()->getStyle('J1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('J1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('K1', 'ALAMAT');
  $objPHPExcel->getActiveSheet()->getStyle('K1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('K1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('L1', 'KAB/KOTA');
  $objPHPExcel->getActiveSheet()->getStyle('L1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('L1')->getFont()->setBold(true);
  
   $objPHPExcel->getActiveSheet()->setCellValue('M1', 'PROVINSI');
  $objPHPExcel->getActiveSheet()->getStyle('M1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('M1')->getFont()->setBold(true);
  
   $objPHPExcel->getActiveSheet()->setCellValue('N1', 'KODE POS');
  $objPHPExcel->getActiveSheet()->getStyle('N1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('N1')->getFont()->setBold(true);
  
  $objPHPExcel->getActiveSheet()->setCellValue('O1', 'FOTO');
  $objPHPExcel->getActiveSheet()->getStyle('O1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('O1')->getFont()->setBold(true);
  
  $schedule_nid = arg(1);
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
           ->entityCondition('bundle', 'registration')
           ->propertyCondition('status', 1)         
           ->fieldCondition('field_reg_schedule', 'target_id', $schedule_nid , '=');
  $result = $query->execute();   
    
    if(isset($result['node'])){
        $i = 1;
        $row = 2;
        foreach(element_children($result['node']) as $reg_nid){
          $reg_node = node_load($reg_nid);

          $noreg = $reg_node->field_reg_no['und'][0]['value'];
            $user_load = user_load($reg_node->field_reg_candidate['und'][0]['target_id']);
            $profile_user = profile2_load_by_user($user_load->uid);

            $nama = $profile_user['data_pribadi']->field_personal_fullname['und'][0]['value'];
            $tipe_sekolah = $profile_user['data_sekolah']->field_sekolah_tipe['und'][0]['value'];
            $nama_sekolah = $profile_user['data_sekolah']->field_sekolah_sma['und'][0]['value'];
            $kota_sekolah_node = node_load($profile_user['data_sekolah']->field_sekolah_kota['und'][0]['target_id']);
            $kota_sekolah = $kota_sekolah_node->field_kota_nama['und'][0]['value'];
            $provinsi_sekolah_node = node_load($kota_sekolah_node->field_kota_provinsi['und'][0]['target_id']);
            $provinsi_sekolah = $provinsi_sekolah_node->title;
            $asal_sekolah = $tipe_sekolah.' '.$nama_sekolah.' - '.$kota_sekolah;

             //get 'alamat' from field collection
           $items = field_get_items('profile2', $profile_user['data_pribadi'], 'field_personal_address');
           foreach($items as $item){
               $fc = field_collection_field_get_entity($item);
               $jalan = $fc->field_address_jalan['und'][0]['value'];
               $rtrw = $fc->field_address_rtrw['und'][0]['value'];
               $norumah = $fc->field_address_norumah['und'][0]['value'];
               $kelurahan = $fc->field_address_kelurahan['und'][0]['value'];
               $kecamatan = $fc->field_address_kecamatan['und'][0]['value'];
               $kota_node = node_load($fc->field_address_kota['und'][0]['target_id']);
               $kota = $kota_node->field_kota_nama['und'][0]['value'];
               $provinsi_node = node_load($kota_node->field_kota_provinsi['und'][0]['target_id']);
               $provinsi = $provinsi_node->title;
               $kodepos = $fc->field_address_kodepos['und'][0]['value'];
           }

           $alamat = "Jl. $jalan RT/RW $rtrw No.$norumah, $kelurahan, $kecamatan";                

            $tanggal_daftar = date('d M Y', $reg_node->created);
            $telp = $profile_user['data_pribadi']->field_personal_telp['und'][0]['value'];

            $foto = theme('user_picture', array('account' => $user_load));
            $is_foto = ($foto)?'OK':'';

            $hp = $profile_user['data_pribadi']->field_personal_hp['und'][0]['value'];
            $email = $user_load->mail;


            $objPHPExcel->getActiveSheet()->setCellValue('A'.$row, $i);
          $objPHPExcel->getActiveSheet()->getStyle('A'.$row)->getFont()->setSize(12);

          $objPHPExcel->getActiveSheet()->setCellValue('B'.$row, $noreg);
          $objPHPExcel->getActiveSheet()->getStyle('B'.$row)->getFont()->setSize(12);

          $objPHPExcel->getActiveSheet()->setCellValue('C'.$row, $nama);
          $objPHPExcel->getActiveSheet()->getStyle('C'.$row)->getFont()->setSize(12);

          $objPHPExcel->getActiveSheet()->setCellValue('D'.$row, $asal_sekolah);
          $objPHPExcel->getActiveSheet()->getStyle('D'.$row)->getFont()->setSize(12);

          $objPHPExcel->getActiveSheet()->setCellValue('E'.$row, $kota_sekolah);
          $objPHPExcel->getActiveSheet()->getStyle('E'.$row)->getFont()->setSize(12);

          $objPHPExcel->getActiveSheet()->setCellValue('F'.$row, $provinsi_sekolah);
          $objPHPExcel->getActiveSheet()->getStyle('F'.$row)->getFont()->setSize(12);      

          //set 'text' agar angka 0 tampil di layar
          $objPHPExcel->getActiveSheet()->setCellValueExplicit('G'.$row, $telp, PHPExcel_Cell_DataType::TYPE_STRING);
          $objPHPExcel->getActiveSheet()->getStyle('G'.$row)->getFont()->setSize(12);             

          //set 'text' agar angka 0 tampil di layar
          $objPHPExcel->getActiveSheet()->setCellValueExplicit('H'.$row, $hp, PHPExcel_Cell_DataType::TYPE_STRING);
          $objPHPExcel->getActiveSheet()->getStyle('H'.$row)->getFont()->setSize(12);

          $objPHPExcel->getActiveSheet()->setCellValue('I'.$row, $tanggal_daftar);
          $objPHPExcel->getActiveSheet()->getStyle('I'.$row)->getFont()->setSize(12);

          $objPHPExcel->getActiveSheet()->setCellValue('J'.$row, $email);
          $objPHPExcel->getActiveSheet()->getStyle('J'.$row)->getFont()->setSize(12);

          $objPHPExcel->getActiveSheet()->setCellValue('K'.$row, $alamat);
          $objPHPExcel->getActiveSheet()->getStyle('K'.$row)->getFont()->setSize(12);

           $objPHPExcel->getActiveSheet()->setCellValue('L'.$row, $kota);
          $objPHPExcel->getActiveSheet()->getStyle('L'.$row)->getFont()->setSize(12);

           $objPHPExcel->getActiveSheet()->setCellValue('M'.$row, $provinsi);
          $objPHPExcel->getActiveSheet()->getStyle('M'.$row)->getFont()->setSize(12);

           $objPHPExcel->getActiveSheet()->setCellValue('N'.$row, $kodepos);
          $objPHPExcel->getActiveSheet()->getStyle('N'.$row)->getFont()->setSize(12);

           $objPHPExcel->getActiveSheet()->setCellValue('O'.$row, $is_foto);
          $objPHPExcel->getActiveSheet()->getStyle('O'.$row)->getFont()->setSize(12);

          $row++;
          $i++; 
        }
    }

  // Naming worksheet 1
  $objPHPExcel->getActiveSheet()->setTitle('Daftar Konfirmasi Pembayaran');

  // Set active sheet index to the first sheet, so Excel opens this as the first sheet
  $objPHPExcel->setActiveSheetIndex(0);

  $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel2007');
  $objWriter->save($output_path);

  //dpm($output_path, 'output_path');


  header('Content-Description: File Transfer');
  header('Content-Type: application/octet-stream');
  header('Content-Disposition: attachment; filename=' . $fname_date . "." . $fname_ext);
  header('Content-Transfer-Encoding: binary');
  header('Expires: 0');
  header('Cache-Control: must-revalidate');
  header('Pragma: public');
  header('Content-Length: ' . filesize($output_path));
  ob_clean();
  flush();
  readfile($output_path);

  unlink($output_path);

  exit;

}
