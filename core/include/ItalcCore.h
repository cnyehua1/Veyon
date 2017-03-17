/*
 * ItalcCore.h - definitions for iTALC Core
 *
 * Copyright (c) 2006-2017 Tobias Doerffel <tobydox/at/users/dot/sf/dot/net>
 *
 * This file is part of iTALC - http://italc.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#ifndef ITALC_CORE_H
#define ITALC_CORE_H

#include <italcconfig.h>

#include <QtEndian>
#include <QString>
#include <QDebug>

#if defined(BUILD_ITALC_CORE_LIBRARY)
#  define ITALC_CORE_EXPORT Q_DECL_EXPORT
#else
#  define ITALC_CORE_EXPORT Q_DECL_IMPORT
#endif

class QCoreApplication;
class QWidget;

class AuthenticationCredentials;
class CryptoCore;
class ItalcConfiguration;
class Logger;

class ITALC_CORE_EXPORT ItalcCore : public QObject
{
	Q_OBJECT
public:
	ItalcCore( QCoreApplication* application, const QString& appComponentName );
	~ItalcCore();

	static ItalcCore* instance();

	static ItalcConfiguration& config()
	{
		return *( instance()->m_config );
	}

	static AuthenticationCredentials& authenticationCredentials()
	{
		return *( instance()->m_authenticationCredentials );
	}

	static void setupApplicationParameters();
	bool initAuthentication( int credentialTypes );

	static QString applicationName();
	static void enforceBranding( QWidget* topLevelWidget );

	typedef enum UserRoles
	{
		RoleNone,
		RoleTeacher,
		RoleAdmin,
		RoleSupporter,
		RoleOther,
		RoleCount
	} UserRole;

	Q_ENUM(UserRole)

	static QString userRoleName( UserRole role );

	UserRole userRole()
	{
		return m_userRole;
	}

	void setUserRole( UserRole userRole )
	{
		m_userRole = userRole;
	}


private:
	static ItalcCore* s_instance;

	ItalcConfiguration* m_config;
	Logger* m_logger;
	AuthenticationCredentials* m_authenticationCredentials;
	CryptoCore* m_cryptoCore;
	QString m_applicationName;
	UserRole m_userRole;

};

#endif
